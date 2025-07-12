#define fm   35
#define bm -35
#define base_spd 20
#define slow_spd 20
#define med_spd 25
#include <GetTouch.h>
#include <GetData.h>
#include <GetUartData.h>
#include <GetButton1.h>
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
#include <SetLCD3Char.h>
#include <SetCentiS.h>
#include <SetLCDClear.h>
#include <SetLCDString.h>
#include <SetServo.h>
#include <SetLED.h>
#define bool int
#define false 0
#define true 1


#define front_diag_left1 3
#define front_diag_left2 2
#define front_diag_left3 1
#define front 4
#define front_diag_right1 5
#define front_diag_right2 6
#define front_diag_right3 7

#define back_diag_left1 5
#define back_diag_left2 6
#define back_diag_left3 7
#define back 4
#define back_diag_right1 3
#define back_diag_right2 2
#define back_diag_right3 1
#define dribbler_spd 105
#define dribbler_stop 90

void mc(float s1, float s2, float s3,float s4)
{ 
// fr,fl,br,bl
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
  
  //--//---///--//--//--/---//--/-/-/-/
  // fr,fl,br,bl
void forward(int spd){
	mc(spd+2,-spd,-spd-2,spd);
}
void left(int spd){
	mc(spd,spd,spd,spd);
}
void right(int spd){
	mc(-spd-2,-spd,-spd+2,-spd);
}
void backward(int spd){
	mc(-spd-3,spd,spd+3,-spd);
}
void diagonal_right(int spd){
	mc(0,-spd,-spd,0);
}
void diagonal_left(int spd){
	mc(spd+2,0,0,spd);
}

void diagonal_left_back(int spd){
	mc(0,spd,spd,0);
}

void diagonal_right_back(int spd){
	mc(-spd-2,0,0,-spd);
}
void stop(){
	mc(0,0,0,0);
}
void kick_on(){
	SetServo(_SERVO_MOS_, dribbler_stop);
	SetCentiS(5);
	SetLED(_LED_KICK_ ,1);
	SetCentiS(10);
	SetLED(_LED_KICK_ ,0);
	stop();
}

int main(void)
{

      X3RCU_Init();

	unsigned int degree = 0;
        int sp;
        int dribbler_cnt=-100;
        int back_cnt=0;
        int ball_pos_fwd,ball_dist_fwd,ball_pos_back,ball_dist_back,uf,ur,ul,flame,ball_front_right2,ball_front_left2,ball_front_right1,ball_front_left1,ball_front;
        int photo_F,photo_B,photo_R,photo_L,photo_RR,photo_RRR,photo_LL,photo_LLL,photo_FF,photo_BB,photo_FFF;
	int cam=0;
	GetCompoI3( _COMPOUNDEYE3_front_ ,14 );
	GetCompoI3( _COMPOUNDEYE3_back_ ,14);
	//SetServo(_SERVO_MOS_,35);
	SetServo(_SERVO_MOS_, dribbler_stop);
	//SetCentiS(2);
	
	/*while(1){
	SetServo(_SERVO_MOS_, 70);
	stop();
	}
	*/
	
while (1)
{
	cam=GetUartData(1, 6);
	ball_front_right2 = GetCompoI3( _COMPOUNDEYE3_front_, 6);
	ball_front_left1 = GetCompoI3( _COMPOUNDEYE3_front_, 3);
	ball_front_right1 = GetCompoI3( _COMPOUNDEYE3_front_, 5);
	ball_front = GetCompoI3( _COMPOUNDEYE3_front_, 4);
	ball_front_left2 = GetCompoI3( _COMPOUNDEYE3_front_, 2);		
        ball_pos_fwd = GetCompoI3( _COMPOUNDEYE3_front_, 8);		   //Bm=distance betwen tha ball and sensor	
	ball_dist_fwd = GetCompoI3( _COMPOUNDEYE3_front_, 9);	    	
        ball_pos_back = GetCompoI3(_COMPOUNDEYE3_back_, 8);		    //Bp=position of the ball from 1 to 7	
	ball_dist_back = GetCompoI3( _COMPOUNDEYE3_back_, 9);	 //bm=9 && bp=8 	
        

	flame=GetIRDist(_IRDISTANCE_flame_);
	
	photo_F = GetPhoto( _PHOTOSENSOR_fp_ );
	photo_FF = GetPhoto( _PHOTOSENSOR_ffp_ );
	photo_FFF = GetPhoto( _PHOTOSENSOR_fffp_ );
	photo_B = GetPhoto( _PHOTOSENSOR_bp_ );
	photo_BB = GetPhoto( _PHOTOSENSOR_bbp_ );
	photo_R = GetPhoto( _PHOTOSENSOR_rp_ );
	photo_L = GetPhoto( _PHOTOSENSOR_lp_ );
	photo_LL = GetPhoto( _PHOTOSENSOR_llp_ );
	photo_LLL = GetPhoto( _PHOTOSENSOR_lllp_ );
        photo_RR = GetPhoto( _PHOTOSENSOR_rrp_ );
        photo_RRR = GetPhoto( _PHOTOSENSOR_rrrp_ );
        
        degree = GetCompassB(_COMPASS_compass_);
        /*
        while(1){
        diagonal_right_back(25);
        SetNS(2);
        stop();
        SetNS(2);
        }
        */
        //while(1){
        //kick_on();
       // SetServo(_SERVO_MOS_, 180);
	//SetNS(5);
        //SetServo(_SERVO_MOS_, 0);
        //SetNS(2);
        //}
       //  SetLCD5Char(100,   0 ,degree, YELLOW, BLACK);
	
	SetLCD5Char(80,  30 ,ball_pos_fwd-ball_front_left2, YELLOW, BLACK);
	SetLCD5Char(80,  80 ,ball_pos_fwd-ball_front_right2, YELLOW, BLACK);
	
	
	
	
	//SetNS(2);
	//SetServo(_SERVO_MOS_, 70);
	//SetNS(2);
	/* backward shot
	while(1){
		SetServo(_SERVO_MOS_, 70);
		backward(slow_spd);
		SetNS(1);
		backward(base_spd);
		//SetServo(_SERVO_MOS_, 70);
		OmniControl(0,0,-110);
		SetCentiS(20);
		stop();
		SetNS(2);
	}
	*/
	
	
      void attack ()
      {
      	
      	bool all3forward=ball_front>90 && ball_front_left1>90 && ball_front_right1>90; 
      	//SetLCDClear(BLACK);
      	
              if(ball_dist_fwd>2 || ball_dist_back>2)
             {
             if(dribbler_cnt<100)	dribbler_cnt++;
             else SetServo(_SERVO_MOS_, dribbler_spd);
                   int all3forward=ball_front>95 && ball_front_left1>95 && ball_front_right1>95; 
    
                   if(flame>1800 && ball_dist_fwd > 100 && (ball_pos_fwd ==front ||ball_pos_fwd ==front_diag_left1||ball_pos_fwd ==front_diag_right1)) {
				
				
				SetLCDClear(CYAN);
				if(cam == 49) {left(base_spd); SetLCDClear(RED);back_cnt=0;}
				else if(cam == 50) {forward(base_spd);SetLCDClear(GREEN);back_cnt=0;}
				else if(cam == 51) {right(base_spd);SetLCDClear(BLUE);back_cnt=0;}
				else if(cam == 52) {kick_on(); SetLCDClear(MAGENTA);back_cnt=0;}
				else if(cam ==53){back_cnt++; SetLCDClear(YELLOW);if(back_cnt>20) backward(base_spd);SetCentiS(15);}
				else {forward(base_spd);}
                        
                        }
                    //    return;
                    else if(ball_pos_fwd==front && ball_dist_fwd >= ball_dist_back)
                   {
                   /*
			if(all3forward || ball_dist_fwd<80) 
				forward(base_spd);
                        else if(ball_front_left1> ball_front_right1 && ball_front_left1>80){
				left(slow_spd);
                        } 
                        
                        else if(ball_front_right1> ball_front_left1 && ball_front_right1>80){
				right(slow_spd);
                        } 
                        else { forward(base_spd);}
			*/
			forward(base_spd);
                   }
                   
                   else if((ball_pos_fwd==front_diag_left2  ) && ball_dist_fwd >= ball_dist_back)  // removed3 condition
                   {
                          if (ball_dist_fwd >90) backward(slow_spd);
			else if(ball_dist_fwd >60) diagonal_left(slow_spd);
			else left(base_spd);
                   }
                   
                   else if(ball_pos_fwd== front_diag_left1 && ball_dist_fwd >= ball_dist_back) // diagonal movement
                   {
			if (ball_front_left1-ball_pos_fwd  > 40)
			diagonal_left(slow_spd);
			else left(base_spd);
                     
                   }             
                   else if(ball_pos_fwd== front_diag_right1 && ball_dist_fwd >= ball_dist_back) // diagonal movement
                   {
                   
                     if (ball_front_right1-ball_pos_fwd > 40)
                         diagonal_right(slow_spd);
                     else right(base_spd);
                     
                   }
                   
		   else if ( (ball_pos_fwd== front_diag_right2 )   && ball_dist_fwd >= ball_dist_back) // removed right3 condition
                   {          
			 if (ball_dist_fwd >90) backward(slow_spd);
			
                            else if(ball_dist_fwd >60) diagonal_right(slow_spd);
			
			else right(base_spd);
                   }  
                   
                   else if(ball_pos_fwd== front_diag_left3 && ball_dist_fwd >= ball_dist_back)
                   {
			if (ball_dist_fwd >70) backward(base_spd);
			//else if(ball_dist_fwd >60) diagonal_left_back(slow_spd);
			else left(base_spd);
                   }
                   else if(ball_pos_fwd== front_diag_right3 && ball_dist_fwd >= ball_dist_back )
                   {
                        if (ball_dist_fwd >70) backward(base_spd);
			
                           // else if(ball_dist_fwd >60) diagonal_right_back(slow_spd); removed right back
			
			else right(base_spd);
                   }
                   
                   // back conditions
		   
                   else if((ball_pos_back== back||ball_pos_back== back_diag_left1) && ball_dist_back >= ball_dist_fwd)
                   {
			   if(ball_dist_back>90)
		           {
				left(base_spd);
			   }
			   else
			   {
				backward(base_spd);
			   }
		   }
		    else if((ball_pos_back== back_diag_left2 || ball_pos_back== back_diag_left3 )  && ball_dist_back >= ball_dist_fwd) //     ////////////////////
		   {
                          backward(base_spd);
		   }
		   else if((ball_pos_back== back_diag_left3 )  && ball_dist_back >= ball_dist_fwd) //     ////////////////////
		   {
                          if(ball_dist_back>90) backward(base_spd);
                          else diagonal_left_back(slow_spd);
		   }
		   else if(ball_pos_back== back_diag_right1 && ball_dist_back >= ball_dist_fwd)
		   {
			if(ball_dist_back>90)
			{
				left(base_spd);
			}
                        else
                        {
                                backward(base_spd);
                        }
                  }
		  else if(ball_pos_back== back_diag_right2 && ball_dist_back >= ball_dist_fwd)
		  {
                              backward(base_spd);     
		  } 
		  else if(ball_pos_back== back_diag_right3 && ball_dist_back >= ball_dist_fwd) // //////////////////////
		  {
                           if(ball_dist_back>90) backward(base_spd);
                          else diagonal_right_back(slow_spd);   
		  } 
		  else
                  {
		        stop();
		        SetLCDClear(Orange);
		        SetNS(1);
		         SetLCDClear(BLACK);
		        SetLCDBack(1);
		        SetLCDString(0, 0, "Unvalid Condition! ", YELLOW, BLACK);
		        SetLCDString(0, 30, "Ball position Front: ", YELLOW, BLACK);
		        SetLCD5Char(80,  30 ,ball_pos_fwd, YELLOW, BLACK);
		        SetLCDString(0, 70, "Ball distance Front: ", YELLOW, BLACK);
		        SetLCD5Char(80,  70 ,ball_dist_fwd, YELLOW, BLACK);
		        SetLCDString(0, 100, "Ball position Back: ", YELLOW, BLACK);
		        SetLCD5Char(80,  100 ,ball_pos_back, YELLOW, BLACK);
		        SetLCDString(0, 150, "Ball distance Back: ", YELLOW, BLACK);
		        SetLCD5Char(80,  150 ,ball_dist_back, YELLOW, BLACK);
		        SetNS(10);
                  }
          
             }
                else
                {
                       stop();
                       SetServo(_SERVO_MOS_, dribbler_stop);
                }
      //---
    }
  
        if (degree >10 && degree <350)		//compass 
	{
		if ( degree > 180 && degree < 350)
		
		{
			sp = 25+(359-degree);
		       OmniControl(0,0,-sp);			
		}
		else if ( degree > 10 && degree <= 180 )
		{
			sp =25+(degree);
		        OmniControl(0,0,sp);	   	  			
		}
         }
         
       else if (photo_L>2300 || photo_LL>2000 || photo_LLL>2000 || photo_R>2500 || photo_B>2200 || photo_BB>2500 || photo_F>2500 || photo_RR>3000 || photo_RRR>2300 || photo_FF>2500 || photo_FFF>2200)
	{
	     //    if(photo_F>2000 || photo_FF>2500)
	        if(photo_F>2500 || photo_FF>2500 || photo_FFF>2200)
		{
		          stop();
		          SetCentiS(5);
		          backward(base_spd);
		          SetCentiS(25);
		}
	      else if(photo_B>2200 || photo_BB>2500)
	      {
		            stop();
		          SetCentiS(5);
		          mc(fm,bm,bm,fm);
		          SetCentiS(25);
		}
	    	       else if(photo_R>2500 || photo_RR>3000 || photo_RRR>2300)
		       {
				    stop();
				SetCentiS(5);
				left(base_spd);
				SetCentiS(25);
			}
			else if(photo_L>2300 || photo_LL>2000 || photo_LLL>2000)
			{
				stop();
				SetCentiS(5);
				right(base_spd);
				SetCentiS(25);
			}
			else if(photo_F>2500 && photo_L>2300)
			{
				stop();
				SetCentiS(20);
				mc(-10,0,0,-10);
				SetCentiS(40);
			}
			else if(photo_F>2500 && photo_R>2500)
			{
				stop();
				SetCentiS(20);
				mc(0,10,10,0);    
				SetCentiS(40);
			}
	}
		else
		{
			attack();
		}
              
        }  //end while
    }   //end program 