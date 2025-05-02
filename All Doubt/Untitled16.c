

#include<graphics.h>
#include<conio.h>
#include<string>
int main()
{   // MOVING CYCLE PROGRAM WITH ARROW KEYS & CHANGING COLOURS WITH FUNCTION KEYS---

    
    // CONTROLS-
    // Cycle_color change- ('F1-F9' )
    // Cycle movements -( right arrow , left arrow )
    
    
    
    
    // Declaration 
    int h=0,page=0;
    int circle1x = 100,circle2x =250;
    int  poly_upline=150,poly_lowerline=100,poly_leftline=100,poly_rightline=225;
    int handle_1=250,handle_2=225,handle_3 =200 ;
    int sheet_1=150,sheet_2=145;
    int speed =5;
    int n=0;
    int Cycle_Color=15;


    // Creating Graphics Window
    DWORD screenwidth=GetSystemMetrics(SM_CXSCREEN);
    DWORD screenHeight=GetSystemMetrics(SM_CYSCREEN);
    initwindow(screenwidth,screenHeight, "Cool Programming Projects",-3);

     char s[30]="Loading...";
    while(1)
    {


        if(n==0)
        {

            setcolor(WHITE);

            rectangle(550+25,320,700+25,340);


            for(int i=0; i<148; i++)
            {
                setcolor(GREEN);
                line(551+i+25,321,551+i+25,339);
                setcolor(WHITE);
                outtextxy(615,350,s);
                delay(10);

            }
        }



        if(n!=0)
        {


            setactivepage(page);
            setvisualpage(1-page);
        }
        cleardevice();
        setcolor(WHITE);

        line(0,500,1400,500);

        //cycle tires

        setcolor(Cycle_Color);
        circle(circle1x,450,50);    //first circle left side
        circle(circle2x,450,50);    //second circle risht side
        
     
        circle(circle1x,450,49);    //first circle left side
        circle(circle2x,450,49);    //second circle risht side
        
         circle(circle1x,450,48);    //first circle left side
        circle(circle2x,450,48);    //second circle risht side



        //cycle polygon

        line(poly_lowerline,450,poly_lowerline+75,450); //lower line of cycle
        line(poly_leftline,450,poly_leftline+50,390); //left line of cycle
        line(poly_upline,390,poly_upline+75,390); //upper line of cycle
        line(poly_rightline,390,poly_rightline-50,450); //right line of cycle
        
         line(poly_lowerline,449,poly_lowerline+75,449); //lower line of cycle
        line(poly_leftline+1,450,poly_leftline+50+1,390); //left line of cycle
        line(poly_upline,391,poly_upline+75,391); //upper line of cycle
        line(poly_rightline-1,390,poly_rightline-50-1,450); //right line of cycle
        
         line(poly_lowerline,448,poly_lowerline+75,448); //lower line of cycle
        line(poly_leftline+2,450,poly_leftline+50+2,390); //left line of cycle
        line(poly_upline,392,poly_upline+75,392); //upper line of cycle
        line(poly_rightline-2,390,poly_rightline-50-2,450); //right line of cycle

        //cycle handle

        line(handle_1,450,handle_1-25,390);
        line(handle_2,390,handle_2-25,340);
        line(handle_3,340,handle_3-20,340);
        
        line(handle_1-1,450,handle_1-26,390);
        line(handle_2-1,390,handle_2-26,340);
        line(handle_3,341,handle_3-20,341);
        
        line(handle_1-2,450,handle_1-27,390);
        line(handle_2-2,390,handle_2-27,340);
        line(handle_3,342,handle_3-20,342);

        //cycle sheet

        line(sheet_1,390,sheet_1,380);
        line(sheet_2,380,sheet_2+10,380);
        
        line(sheet_1+1,390,sheet_1+1,380);
        line(sheet_2,381,sheet_2+10,381);
        
        line(sheet_1-1,390,sheet_1-1,380);
        line(sheet_2,379,sheet_2+10,379);
        





        if(n==0)
        {


            setcolor(GREEN);

            settextstyle(0,HORIZ_DIR,2);
            outtextxy(440,570,"Press Any Key To Continue... ");
            getch();
            n++;

        }

        if(n==1)
        {
         setcolor(RED);
         rectangle(550,570,600,620);
         rectangle(549,571,599,619);
         rectangle(548,572,598,618);
         setcolor(RED);
         line(560,595,590,595);
         line(560,595-1,590,595-1);
         line(560,595+1,590,595+1);
         int points[8]={560,595,570,590,570,600,560,595};
         setfillstyle(SOLID_FILL,RED);
         fillpoly(4,points);

         rectangle(720,570,770,620);
         rectangle(719,571,769,619);
         rectangle(718,572,768,621);
         
         line(730,595,760,595);
         line(730,595+1,760,595+1);
         line(730,595-1,760,595-1);
         int points2[8]={760,595,750,590,750,600,760,595};;
         fillpoly(4,points2);




        }

        if(GetAsyncKeyState(VK_LEFT))
        {

            circle1x       -= speed ;
            circle2x       -= speed ;
            poly_upline    -= speed ;
            poly_lowerline -= speed ;
            poly_leftline  -= speed ;
            poly_rightline -= speed ;
            handle_1       -= speed ;
            handle_2       -= speed ;
            handle_3       -= speed ;
            sheet_1        -= speed ;
            sheet_2        -= speed  ;
        }


        if(GetAsyncKeyState(VK_RIGHT))
        {

            circle1x       += speed ;
            circle2x       += speed ;
            poly_upline    += speed ;
            poly_lowerline += speed ;
            poly_leftline  += speed ;
            poly_rightline += speed ;
            handle_1       += speed ;
            handle_2       += speed ;
            handle_3       += speed ;
            sheet_1        += speed ;
            sheet_2        += speed  ;
        }
        if(GetAsyncKeyState(VK_F1))
        {
        	Cycle_Color=15;
        	
		}
		if(GetAsyncKeyState(VK_F2))
		{
			Cycle_Color=14;
		}
		if(GetAsyncKeyState(VK_F3))
		{
			Cycle_Color=13;
		}
		if(GetAsyncKeyState(VK_F4))
		{
			Cycle_Color=12;
		}
        if(GetAsyncKeyState(VK_F5))
        {
        	Cycle_Color=11;
		}
		if(GetAsyncKeyState(VK_F6))
		Cycle_Color=10;
		if(GetAsyncKeyState(VK_F7))
		Cycle_Color=9;
		if(GetAsyncKeyState(VK_F8))
		Cycle_Color=3;
		if(GetAsyncKeyState(VK_F9))
		Cycle_Color=5;
		
        delay(10);
        page=1-page;
    }

    getch();
    closegraph();
    return 0;

}
