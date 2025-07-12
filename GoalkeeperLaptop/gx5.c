#define fm 35
#include <SetSwitch.h>
#include <GetCompoI2.h>
#include <GetCompoI3.h>
#include <GetPhoto.h>
#include "JMLib.c"
#include <SetNS.h>
#include <SetMotor.h>
#include "HardwareInfo.c"
#include <SetTenthS.h>
#include <GetIRDist.h>
#include <GetCompassB.h>
#include <SetLCDBack.h>
#include <SetLCD5Char.h>
#include <SetCentiS.h>
#include <SetLCDString.h>

void mc(float s1, float s2, float s3,float s4)
{ 
if (s1 > 0 ) SetMotor(_MOTOR_m1_,0, s1);
else SetMotor(_MOTOR_m1_, 2, -s1);
if (s2 > 0 ) SetMotor(_MOTOR_m2_, 0, s2);
else SetMotor(_MOTOR_m2_, 2, -s2);
if (s3 > 0 ) SetMotor(_MOTOR_m3_, 0, s3);
else SetMotor(_MOTOR_m3_, 2, -s3);
if (s4 > 0 ) SetMotor(_MOTOR_m4_, 0, s4);
else SetMotor(_MOTOR_m4_, 2, -s4);
}

   void OmniControl(float x, float y, float w)
{
float s1,s2,s3,s4;

s1 =      -0.30*x        +0.58*y       +0.33*w;
s2 =      -0.30*x         -0.58*y       +0.33*w;
s3 =      -0.30*x         -0.58*y        -0.33*w;
s4 =      -0.30*x        +0.58*y        -0.33*w;

mc(s1,s2,s3,s4);
}
  
int main(void)
{

      X4RCU_Init();

	unsigned int degree = 0;
        int sp,count;
        int bpf,bmf,bpb,bmb,ur,ul,ub;
       int photo_F,photo_B,photo_R,photo_L,photo_RR,photo_LL,photo_BB;
	GetCompoI3( _COMPOUNDEYE3_front_ ,14 );
	GetCompoI3( _COMPOUNDEYE3_back_ ,14);


while (1)
{

	ur=GetIRDist(_IRDISTANCE_ur_);
	ul=GetIRDist(_IRDISTANCE_ul_);
	ub=GetIRDist(_IRDISTANCE_ub_);
	
        bpf = GetCompoI3( _COMPOUNDEYE3_front_, 8);		   //Bm=distance betwen tha ball and sensor	
	bmf = GetCompoI3( _COMPOUNDEYE3_front_, 9);	    	
        bpb = GetCompoI3(_COMPOUNDEYE3_back_, 8);		    //Bp=position of the ball from 1 to 7	
	bmb = GetCompoI3( _COMPOUNDEYE3_back_, 9);	 //bm=9 && bp=8 	

	photo_F = GetPhoto( _PHOTOSENSOR_fp_ );
	photo_B = GetPhoto( _PHOTOSENSOR_bp_ );
	photo_R = GetPhoto( _PHOTOSENSOR_rp_ );
	photo_L = GetPhoto( _PHOTOSENSOR_lp_ );
       // photo_BB = GetPhoto( _PHOTOSENSOR_bbp_ );
	photo_RR = GetPhoto( _PHOTOSENSOR_rrp_ );
	photo_LL = GetPhoto( _PHOTOSENSOR_llp_ );
 
	degree = GetCompassB(_COMPASS_compass_);

        void keeper ()
	{
	      if(bmf>5 || bmb>5){
	        if(ub>350 || ur<500 || ul<500 || ub<300)
         {
		int mx,my;
		//my =  420 - UB  //between 360 and 500
		SetLCDString(50, 50, "Other", RED, BLACK);
		if ( ub > 370 )
			my = -30;
			//OmniControl(0,-70,0);
		else if ( ub < 300 )
			my = 30;
			//OmniControl(0,70,0);
		else
			my=0;
	
		if (ur<550)
			OmniControl(-50,my,0);
		else if (ul<550)
			OmniControl(50,my,0);
		else
			OmniControl(0,my,0);
	}
		if(bpf==4)
       {
            if(bmf>65)
           {
             count ++;
               mc(0,0,0,0);
                   if(count>500)
                   {
         /*      mc(100,-100,-100,100);
                   SetCentiS(40);
                   count = 0;   */
			   if(ur<600)
			   {
			       mc(-10,-10,-10,-10);
			       SetCentiS(15);
			       mc(0,0,0,0);
			       SetCentiS(5);
			       mc(5,5,-5,-5);
			       SetCentiS(8);
			       mc(20,-20,-20,20);
			       SetCentiS(35);
			       count = 0;
			   }
			   else if(ul<600)
			   {
			      mc(10,10,10,10);
			       SetCentiS(15);
			       mc(0,0,0,0);
			       SetCentiS(2);
			       mc(-5,-5,5,5);
			       SetCentiS(8);
			       mc(20,-20,-20,20);
			       SetCentiS(35);
			       count = 0;
			   }
			   else
			   {
			       mc(20,-20,-20,20);
			       SetCentiS(35);
			       count = 0;
			    }
			   
                   
                   
			}
		 }
		   else 
		   {
		   int mx,my;
		   if ( ub > 350 ) my = -30;
		   else if ( ub < 230 ) my = 30;
		   else my=0;
		OmniControl(0,my,0);
		   count =0;
		   }
      }
 
		   else if(bpf>4 && bpf<7)
		   {
			 if (ur<550)
			{
			      mc(0,0,0,0);
			}
			else   
		       {
			      mc(-fm,-fm,-fm,-fm);
			}
		   }
		   else if(bpf<4 && bpf>1)
		   {
			if (ul<550)
			{
			      mc(0,0,0,0);
			}
			else   
		       {
			   mc(fm,fm,fm,fm);
			}
		   }
		   else if(bpf==1 && bpb==7)
		   {
			  if (ul<550)
			{
			      mc(0,0,0,0);
			}
			else   
		       {
			    mc(fm,fm,fm,fm);
		       } 
		   }
		   else if(bpf==7 && bpb==1)
		   {
			 if (ur<550)
			{
			      mc(0,0,0,0);
			}
			else   
		       {
			   mc(-fm,-fm,-fm,-fm);
			}
		    }  
		    else if(bpb>1 && bpb<7)
		    {
			      mc(0,0,0,0);
		    }   
       
	      }
                   
           
	else 											//return base
       {
          
       
	   if(ub>350 || ur<550 || ul<500 || ub<300)
         {
		SetLCD5Char(20, 20, ub, YELLOW, BLACK);
		int mx,my;
		//my =  420 - UB  //between 360 and 500
	
		if ( ub > 350 ){
		my = -30;
			SetLCDString(50, 50, "Back", RED, BLACK);
		}
			
			//OmniControl(0,-70,0);
		else if ( ub < 230 ){
		my = 30;
		SetLCDString(50, 50, "Front", GREEN, BLACK);
		}
			
			//OmniControl(0,70,0);
		else{
		my=0;
		SetLCDString(50, 50, "ELSE", BLUE, BLACK);
		}
			
	
		if (ur<660)
			OmniControl(-50,my,0);
		else if (ul<650)
			OmniControl(50,my,0);
		else
			OmniControl(0,my,0);
	}
	else{
	SetLCDString(50, 50, "Out of Condition", RED, BLACK);
	}
	}
	
      
  
      
        }
        
        // start code
        
        
        if (degree >10 && degree <350)		//compass 
	{
		if ( degree > 180 && degree < 355 )
		{
			sp = 10+(360-degree);
			OmniControl(0,0,-sp);			
		}
		else if ( degree > 5 && degree < 180 )
		{
			sp =10+(degree);
			OmniControl(0,0,sp);	   	  			
		}
	}	
	
	 
                 
                 else
                 {
                    keeper();
                 }
      
             }  //end while
             
             }   //end program
                    