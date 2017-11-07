#include "DarkGDK.h"
#include "math.h"
#include "SC_Collision.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>

bool soundStart = true;
bool soundPlaying = true;
float test;
float test2;
bool camFlag = true;
int cam;
std::string fileName;
std::string fileName2;
float angy = 0;
float dX,dY,dZ;
float base = 0;
float distance=0;
float cameraVec;
float fCameraAngleX = 0.0f;
float fCameraAngleY = 0.0f;
float radius = 7.0f;
float power = 0.5;
float x,y,z;
float i=0;
int seite=1;
int i2;
float nx,ny,nz;
float dx,dy,dz;
float forw,left;
float boostF,boostL;
float down;
float gravitation = 0.5;
float gravi = gravitation;
float jump = 30;
bool dooropen = false;
bool ground = false;
bool spacepressed = false;
bool selectMode = false;
float bounce;
bool StartMenu = true;
bool StartSelect = true;
bool Ingame = false;
int level = 0;
bool stop = true;
bool finishfly = false;
bool cheat = true;
bool dead = false;
bool sound = true;
bool boostsound= true;
const char *temp;
char *temp2;
char *Dir;
OPENFILENAME ofn;       // common dialog box structure
char szFile[260];       // buffer for file name
HWND hwnd;              // owner window
HANDLE hf;              // file handle

std::string Replace(std::string source,std::string find,std::string repl)
{
    int pos ;
    do
    {
        pos = source.find(find);
        if (pos!=-1)  source.replace(pos, find.length(), repl);
    }
    while (pos!=-1);
    return source;
}

void ExitLevel()
{
	down =0;
	forw =0;
	left= 0;
	cameraVec = 0;
	angy= 0;
	dooropen = false;
	y=0;x=0;z=0;ny=0;nx=0;nz=0;
	i=0;
	cheat = true;
	finishfly = false;
	Ingame=false;
	StartSelect = true;
	selectMode = true;
	dead = false;
	
}
void Finish1()
{
	int collide = SC_SphereCast(23,x,y,z,y,y+down,z,radius,0);
	if (collide>0)
	{
		if (!dooropen)
		{
			if (cheat)
			{
			dbLoadImage("Media/Picture/cheater.png",30);
			dbSprite(31,0,0,30);
			cheat = false;
			}
		}
		else
		{
			stop = false;
			finishfly = true;
			dbLoadImage("Media/Picture/WinScreen.png",30);
			dbSprite(31,0,0,30);
			cameraVec = 0;
			angy=0;
		}
	}
	if (finishfly)
	{

		dbPointCamera(x,y,z);
		y +=1;
		y *=1.089;
		dbPositionObject(1,x,y,z);
		if (y > 5000)
		{
			ExitLevel();
		}
	}

}
void Finish2()
{
	int collide = SC_SphereCast(23,x,y,z,x,y+down,z,radius,0);
	if (collide>0)
	{
		stop = false;
		finishfly = true;
		dbLoadImage("Media/Picture/WinScreen.png",30);
		dbSprite(31,0,0,30);
		cameraVec =0;
		angy=0;
		y=0;
		collide = 0;
	}

	if (finishfly)
	{

		dbPointCamera(x,y,z);
		y +=1;
		y *=1.089;
		dbPositionObject(1,x,y,z);
		if (y>5000)
		{
			ExitLevel();
		}
	}
}
void isDead()
{
	if (y < -5000)
	{
		dead = true;
		stop = false;
		y =0;
		dbLoadImage("Media/Picture/GameOverScreen.png",30);
		dbSprite(31,0,0,30);
		dbText(1,1,"C o n t r o l s:");
		dbText(30,20,"M o v e        W  A  S  D    O r   A r r o w    K e y s");
		dbText(30,40,"J u m p        S p a c e");
		dbText(30,60,"P r e s s  \"C\" t o  M o v e  C a m e r a   w i t h   M o u s e");
		dbSync();
	}
	if (dead)
	{
			for (int warten=0;warten<1500;warten++)
			{
			dbWait(1);
			}
			ExitLevel();
	}
}
void OpenDoor()
{
	if (dooropen && i<50)
	{
		i+= 0.5 ;
		dbTurnObjectRight(21,-0.5);
		dbMoveObjectLeft(21,-0.5);
		SC_UpdateObject(21);
		dbPositionObject(22,0,0-i,0);
		SC_UpdateObject(22);
	}
	
}
void ButtonPressed()
{
	int collide = SC_SphereCast(22,x,y,z,y,y+down,z,radius,0);
	if (collide>0)
	{
		dooropen = true;
	}
}
void LoadMap0()
{
	dbLoadObject(szFile,2);
	dbPositionObject(1,0,1000,0);
	dbPositionObject(2,0,0,0);
	SC_SetupComplexObject(2,2,2);
	SC_AllowObjectScaling(2);
	dbScaleObject(2,500,500,500);
	SC_UpdateObject(2);

	
}
void DeloadMap0()
{
	dbDeleteObject(2);
	dbDeleteImage(30);
	dbDeleteSprite(31);	
}
void LoadMap1()
{
	//Map Laden
	dbLoadObject( "Media/Models/Level_01_ver_07.x", 2);
	SC_SetupComplexObject(2,2,2);
	SC_AllowObjectScaling(2);
	dbYRotateObject(2,-90);
	dbScaleObject(2,200,200,200);
	SC_UpdateObject(2);
	
	
	
	//Linke Türe
	dbLoadObject( "Media/Models/LeftDoor.x",21);
	
	SC_SetupComplexObject(21,2,2);
	SC_AllowObjectScaling(21);
	dbYRotateObject(21,-90);
	dbScaleObject(21,200,200,200);
	SC_UpdateObject(21);
	//Schalter
	dbLoadObject("Media/Models/Button.x",22);
	SC_SetupComplexObject(22,2,2);
	SC_AllowObjectScaling(22);
	dbYRotateObject(22,-90);
	dbScaleObject(22,200,200,200);
	SC_UpdateObject(22);
	// Ziel
	dbLoadObject("Media/Models/Finish.x",23);
	SC_SetupComplexObject(23,2,2);
	SC_AllowObjectScaling(23);
	dbYRotateObject(23,-90);
	dbScaleObject(23,200,200,200);
	SC_UpdateObject(23);
	//Ball setzen
	dbPositionObject(1,245,100,-1500);
	//Kamera Setzen
	dbPositionCamera(265,5000,-10000);
	dbPointCamera(245,100,-1500);
}
void DeloadMap1()
{
	dbDeleteObject(2);
	dbDeleteObject(20);	
	dbDeleteObject(21);
	dbDeleteObject(22);
	dbDeleteObject(23);
	dbDeleteImage(30);
	dbDeleteSprite(31);


}
void LoadMap2()
{
	//Map Laden
	dbLoadObject ( "Media/Models/LevelJump.x", 2);
	SC_SetupComplexObject(2,2,2);
	SC_AllowObjectScaling(2);
	dbScaleObject(2,95,95,95);
	dbPositionObject(2,-20,0,0);
	SC_UpdateObject(2);	
	
	dbLoadObject ( "Media/Models/Finish2.x", 23);
	SC_SetupComplexObject(23,2,2);
	SC_AllowObjectScaling(23);
	dbScaleObject(23,95,95,95);
	dbPositionObject(23,-20,0,0);
	SC_UpdateObject(23);
	//Spieler Positionieren
	dbPositionObject(1,40,200,-2300);
	//Kamera Setzen
	dbPositionCamera(265,5000,-10000);
	dbPointCamera(20,200,-2300);

}
void DeloadMap2()
{
	dbDeleteObject(2);
	dbDeleteObject(23);
	dbDeleteImage(30);
	dbDeleteSprite(31);
}
void LoadMap3()
{

	
	//Map Laden
	dbLoadObject ( "Media/Models/CrazyLevel.x", 2);
	SC_SetupComplexObject(2,2,2);
	SC_AllowObjectScaling(2);
	dbScaleObject(2,500,500,500);
	dbPositionObject(2,0,0,0);
	SC_UpdateObject(2);	
	

	//Ball setzen
	dbPositionObject(1,20,1000,50);
	//Kamera Setzen
	dbPositionCamera(265,5000,-10000);
	dbPointCamera(0,200,0);	
}
void LoadMap4()
{
	dbLoadObject ( "Media/Models/Level_03_ver01.x", 2);
	SC_SetupComplexObject(2,2,2);
	SC_AllowObjectScaling(2);
	dbScaleObject(2,300,300,300);
	SC_UpdateObject(2);	

	dbLoadObject ( "Media/Models/Goal_Level_3.x", 23);
	SC_SetupComplexObject(23,2,2);
	SC_AllowObjectScaling(23);
	dbScaleObject(23,300,300,300);
	SC_UpdateObject(23);	

	dbPositionObject(1,0,100,100);
	//Kamera Setzen
	dbPositionCamera(0,1000,-10000);
	dbPointCamera(dbObjectPositionX(1),dbObjectPositionY(1),dbObjectPositionZ(1));

}
void DeloadMap4()
{
	dbDeleteObject(2);
	dbDeleteObject(23);
	dbDeleteImage(30);
	dbDeleteSprite(31);
}
void LoadMap5()
{
	dbLoadObject ( "Media/Models/Level_04_ver_01.x", 2);
	SC_SetupComplexObject(2,2,2);
	SC_AllowObjectScaling(2);
	dbScaleObject(2,200,200,200);
	SC_UpdateObject(2);	

	dbLoadObject ( "Media/Models/Goal_Level_4.x", 23);
	SC_SetupComplexObject(23,2,2);
	SC_AllowObjectScaling(23);
	dbScaleObject(23,200,200,200);
	SC_UpdateObject(23);	

	dbPositionObject(1,660,100,-3600);
	//Kamera Setzen
	dbPositionCamera(660,4000,-10000);
	dbPointCamera(dbObjectPositionX(1),dbObjectPositionY(1),dbObjectPositionZ(1));
}
void LoadPlayer()
{
	// Ball Laden
	dbMakeObjectSphere( 1,radius*2.0f );
	dbPositionObject(1,0,0,0);
	SC_SetupObject(1,0,1);
	//Skybox Laden
	dbLoadObject ( "Media/Models/skybox.x", 3 );
	dbSetObjectLight ( 3, 0 );
	dbScaleObject ( 3, 90000, 90000, 90000 );
	dbSetCameraRange ( 1.0f, 90000.0f );
	//Sounds Laden
	dbLoadSound("Media/Sounds/tock.wav",50);
	dbLoadSound("Media/Sounds/boing.wav",51);
	dbLoadSound("Media/Sounds/start.wav",52);
	dbLoadSound("Media/Sounds/mid.wav",53);
	dbLoadSound("Media/Sounds/go.wav",54);
}

void DeloadPlayer()
{
	dbDeleteObject(1);
	dbDeleteObject(3);
}
void DelSpritesStart()
{


	dbDeleteSprite(14);
	dbDeleteSprite(17);
	dbDeleteSprite(19);

	dbDeleteImage(16);
	dbDeleteImage(18);
}
void DelSpritesSelect()
{
	dbDeleteImage(8);
	dbDeleteSprite(9);
	dbDeleteImage(10);
	dbDeleteSprite(11);
	dbDeleteImage(12);
	dbDeleteSprite(13);
	dbDeleteImage(14);
	dbDeleteSprite(14);
	dbDeleteImage(20);
	dbDeleteSprite(21);
	dbDeleteSprite(22);
	dbDeleteImage(23);
	dbDeleteSprite(24);
	dbDeleteImage(25);
	dbDeleteSprite(26);
	dbDeleteSprite(27);
	dbDeleteSprite(28);
	dbDeleteImage(40);
	dbDeleteSprite(41);
	dbDeleteSprite(42);
	dbDeleteImage(43);
	dbDeleteSprite(44);
	dbDeleteImage(45);
	dbDeleteSprite(46);
}
/*
void getLevel()
{
	dbShowMouse();
	// Initialize OPENFILENAME
	ZeroMemory(&ofn, sizeof(OPENFILENAME));
	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = hwnd;
	ofn.lpstrFile = szFile;
	ofn.nMaxFile = sizeof(szFile);
	ofn.lpstrFilter = "DirectX\0*.x\0";
	ofn.nFilterIndex = 1;
	ofn.lpstrFileTitle = NULL;
	ofn.nMaxFileTitle = 0;
	ofn.lpstrInitialDir = NULL;
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

	// Display the Open dialog box. 

	if (GetOpenFileName(&ofn)==TRUE) 
	{
		hf = CreateFile(ofn.lpstrFile, GENERIC_READ,
			0, (LPSECURITY_ATTRIBUTES) NULL,
			OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL,
			(HANDLE) NULL);
	}
	dbHideMouse();
}
*/
BOOL getLevel( void ) // Funktion ruft ein openfile dialog auf und speichert den pfad in variable szFile
{
	dbShowMouse();
	// Initialize OPENFILENAME
	ZeroMemory(&ofn, sizeof(OPENFILENAME));
	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = 0;
	ofn.lpstrFile = szFile;
	ofn.nMaxFile = sizeof(szFile);
	ofn.lpstrFilter = "DirectX\0*.x\0";
	ofn.nFilterIndex = 1;
	ofn.lpstrFileTitle = NULL;
	ofn.nMaxFileTitle = 0;
	ofn.lpstrInitialDir = NULL;
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

	// Display the Open dialog box. 
	return GetOpenFileName(&ofn);
}
void LevelSelect()
{
		if (StartSelect)
		{
		dbCreateAnimatedSprite(14,"Media/Picture/Cursor.png",4,2,14);
		dbSprite(14,1,1,14);
		dbSetSpritePriority(14,5);
		dbLoadImage("Media/Picture/Background.png",8);
		dbSprite(9,0,0,8);
		dbLoadImage("Media/Picture/ExitButton_ver1.png",10);
		dbSprite(11,500,500,10);
		dbSetSpritePriority(11,2);
		dbLoadImage("Media/Picture/ExitButtonAC_ver1.png",12);
		dbSprite(13,500,500,12);
		dbSetSpritePriority(13,1);
		dbLoadImage("Media/Picture/buttonImp.png",43);
		dbSprite(44,100,500,43);
		dbSetSpritePriority(44,1);
		dbLoadImage("Media/Picture/buttonImpAC.png",45);
		dbSprite(46,100,500,45);
		dbSetSpritePriority(46,2);
		StartSelect= false;
		}

		dbSprite(14,dbMouseX(),dbMouseY(),14);
		dbPlaySprite(14,1,8,80);
		if (dbSpriteCollision(14,11)==1)
		{
			dbHideSprite(11);
			if (dbMouseClick()==1)
			{
				exit(0);
			}
		}
		else
		{
			dbShowSprite(11);
		}
		dbLoadImage("Media/Picture/Button.png",20);
		dbSprite(21,750,280,20);
		dbScaleSprite(21,150);
		dbSetSpritePriority(21,5);
		dbSprite(22,50,340,20);
		dbScaleSprite(22,150);
		dbSetSpritePriority(22,5);
		dbRotateSprite(22,180);
		dbLoadImage("Media/Picture/ButtonAC.png",40);
		dbSprite(41,750,280,40);
		dbScaleSprite(41,150);
		dbSprite(42,50,340,40);
		dbScaleSprite(42,150);
		dbRotateSprite(42,180);

		if (dbSpriteCollision(14,21)==1)
		{
			dbHideSprite(21);
		}
		else
		{
			dbShowSprite(21);
		}
		if (dbSpriteCollision(14,22)==1)
		{
			dbHideSprite(22);
		}
		else
		{
			dbShowSprite(22);
		}
		if (dbSpriteCollision(14,46)==1)
		{
			dbHideSprite(46);
		}
		else
		{
			dbShowSprite(46);
		}
		if (dbSpriteCollision(14,21)==1)
		{
			if (dbMouseClick()==1)
			{
				
				seite ++;
				if (seite >2)(seite =2);
			}
		}
		if (dbSpriteCollision(14,22)==1)
		{
			if (dbMouseClick()==1)
			{
				seite--;
				if(seite<1)(seite=1);
			}
		}
		switch(seite)
		{
		case 1: 		
						dbDeleteImage(23);
						dbDeleteSprite(24);
						dbDeleteImage(25);
						dbDeleteSprite(26);
						dbLoadImage("Media/Picture/level1Screen.png",23);
						dbSprite(24,50,50,23);
						dbSetSpritePriority(24,1);
						dbLoadImage("Media/Picture/level2Screen.png",25);
						dbSprite(26, 400,50,25);
						dbSetSpritePriority(26,1);
						break;
		case 2:		
						dbDeleteImage(23);
						dbDeleteSprite(24);
						dbDeleteImage(25);
						dbDeleteSprite(26);
						dbLoadImage("Media/Picture/level3Screen.png",23);
						dbSprite(27,50,50,23);
						dbLoadImage("Media/Picture/level4Screen.png",25);
						dbSprite(28,400,50,25);
						break;

		}
		
		if (dbKeyState(17)==1)
		{
			level = 3;
			LoadPlayer();
			LoadMap3();
			selectMode=false;
			Ingame=true;
			dead =false;
			stop = true;
			y=0;
		}
		if (dbSpriteCollision(14,44)==1)
		{
			
			 if(dbMouseClick()==1)
			 {
				Dir = dbGetDir();
				if (getLevel())
				{
					dbSetDir(Dir);
					level = 0;
					LoadPlayer();
					LoadMap0();
					selectMode=false;
					Ingame= true;
				}
			 }
		}

			
		if (dbSpriteCollision(14,24)==1)
		{
			
			 if(dbMouseClick()==1)
			 {
				level =1;
				LoadPlayer();
				LoadMap1();
				selectMode=false;
				Ingame = true;
				dead =false;
				stop = true;
				y=0;				
			 }
		}
		if (dbSpriteCollision(14,26)==1)
		{
			if(dbMouseClick()==1)
			{
				level = 2;
				LoadPlayer();
				LoadMap2();
				selectMode=false;
				Ingame =true;
				dead =false;
				stop = true;
				y=0;
			}
		}
		if (dbSpriteCollision(14,27)==1)
		{
			if(dbMouseClick()==1)
			{
				level = 4;
				LoadPlayer();
				LoadMap4();
				selectMode=false;
				Ingame =true;
				dead =false;
				stop = true;
				y=0;
			}
		}
		if (dbSpriteCollision(14,28)==1)
		{
			if(dbMouseClick()==1)
			{
				level = 6;
				LoadPlayer();
				LoadMap5();
				selectMode=false;
				Ingame =true;
				dead =false;
				stop = true;
				y=0;
			}
		}
}
void Menu()
{	
	if (StartMenu) 
	{
		dbHideMouse();
		dbSetDisplayMode(800,600,32);
		dbLoadImage("Media/Picture/Background.png",8);
		dbSprite(9,0,0,8);
		dbLoadImage("Media/Picture/ExitButton_ver1.png",10);
		dbSprite(11,500,500,10);
		dbSetSpritePriority(11,2);
		dbLoadImage("Media/Picture/ExitButtonAC_ver1.png",12);
		dbSprite(13,500,500,12);
		dbSetSpritePriority(13,1);
		dbLoadImage("Media/Picture/StartButton_ver1.png",16);
		dbSprite(17,100,500,16);
		dbSetSpritePriority(17,2);
		dbLoadImage("Media/Picture/StartButtonAC_ver1.png",18);
		dbSprite(19,100,500,18);
		dbSetSpritePriority(19,1);
		dbCreateAnimatedSprite(14,"Media/Picture/Cursor.png",4,2,14);
		dbSprite(14,1,1,14);
		dbSetSpritePriority(14,5);
		StartMenu = false;
	}
	dbSprite(14,dbMouseX(),dbMouseY(),14);
	dbPlaySprite(14,1,8,80);

	if (dbSpriteCollision(14,11)==1)
	{
		dbHideSprite(11);
		if (dbMouseClick()==1)
		{
			exit(0);
		}
	}
	else
	{
		dbShowSprite(11);
	}
	if(dbSpriteCollision(14,17)==1)
	{
		dbHideSprite(17);
		if (dbMouseClick()==1)
		{
			LevelSelect();
			DelSpritesStart();
			StartSelect= true;
			selectMode=true;
		}

	}
	else
	{
		dbShowSprite(17);
	}
}
void MovePlayer()
{		

		x = dbObjectPositionX(1);
		y = dbObjectPositionY(1);
		z = dbObjectPositionZ(1);

		dX = x -dbCameraPositionX();
		dZ = z -dbCameraPositionZ();
		dY = y -dbCameraPositionY();
		distance = dbSQRT((dY*dY)+(dX*dX)+(dZ*dZ));
		
		

		int collideCam = SC_RayCast(0,x,y,z,dbCameraPositionX(),dbCameraPositionY(),dbCameraPositionZ(),1);

		if (collideCam >0)
		{
			dbPositionCamera(SC_GetCollisionSlideX(),SC_GetCollisionSlideY(),SC_GetCollisionSlideZ());
		}



		dbSetTextFont("Snap ITC");
		dbSetTextSize(20);
		dbText(1,1,"C o n t r o l s:");
		dbText(30,20,"M o v e        W  A  S  D    O r   A r r o w    K e y s");
		dbText(30,40,"J u m p        S p a c e");
		dbText(30,60,"P r e s s  \"C\" t o  M o v e  C a m e r a   w i t h   M o u s e");
		angy = dbCameraAngleY();
		cameraVec = dbATANFULL(left,forw);
		

		if (dbKeyState(0x2e)==1)
		{
			if (camFlag)
			{
				if (cam == level)
				{
					cam = 5;
				}
				else
				{
					cam = level;
				}
				camFlag = false;
			}
		}
		else
		{
			camFlag = true;
		}


		
			
if (stop)
{

		switch(cam)
		{			
			case 0: 
				//dbControlCameraUsingArrowKeys ( 0, 2.0f, 2.0f );
				//fCameraAngleX = dbWrapValue ( fCameraAngleX + dbMouseMoveY ( )* 0.4f );
				//fCameraAngleY = dbWrapValue ( fCameraAngleY + dbMouseMoveX ( )* 0.4f );
				//dbXRotateCamera ( fCameraAngleX );
				//dbYRotateCamera ( fCameraAngleY );
				if (distance < 400)
				{	
					dbPointCamera(x,y,z);
				}
				else
				{
					dbPointCamera(x,y,z);
					dbSetCameraToFollow(x,y,z,cameraVec,430,150,25,0);
				}
					break;
			case 3:
				if (distance < 200)
				{
					dbPointCamera(x,y,z);
				}
				else
				{
					dbPointCamera(x,y,z);
					dbSetCameraToFollow(x,y,z,cameraVec,220,80,25,1);
				}
					break;
			case 5:
				//dbControlCameraUsingArrowKeys ( 0, 20.0f, 2.0f );
				//fCameraAngleX = dbWrapValue ( fCameraAngleX + dbMouseMoveY ( )* 0.4f );
				//fCameraAngleY = dbWrapValue ( fCameraAngleY + dbMouseMoveX ( )* 0.4f );
				//dbXRotateCamera ( fCameraAngleX );
				//dbYRotateCamera ( fCameraAngleY );
				dbYRotateObject( 1,dbObjectAngleY(1) + dbMouseMoveX()/3.0f );
				dbXRotateObject( 1,dbObjectAngleX(1) + dbMouseMoveY()/3.0f );
				dbPositionCamera( dbObjectPositionX(1),dbObjectPositionY(1),dbObjectPositionZ(1) );
				dbRotateCamera( dbObjectAngleX(1),dbObjectAngleY(1),dbObjectAngleZ(1) );
				dbMoveCamera( -400 );
				break;
			default:
				if (distance < 400)
				{
					dbPointCamera(x,y,z);
				}
				else
				{
					dbPointCamera(x,y,z);
					dbSetCameraToFollow(x,y,z,cameraVec,410,150,30,1);
				}
				break;
		}
		if (dbKeyState(32) || dbRightKey() ) { left = left + dbCos(angy); forw = forw - dbSin(angy); } //||dbKeyState(24) || dbKeyState(37)
		if (dbKeyState(30) || dbLeftKey()  ) { left = left - dbCos(angy); forw = forw + dbSin(angy); } //||dbKeyState(25)|| dbKeyState(38)
		if (dbKeyState(31) || dbDownKey()  ) { left = left - dbSin(angy); forw = forw - dbCos(angy); } //|| dbKeyState(23) || dbKeyState(36)
		if (dbKeyState(17) || dbUpKey() ) { left = left + dbSin(angy); forw = forw + dbCos(angy); }	   //|| dbKeyState(22) || dbKeyState(35)
		
		if (dbKeyState(24)) { left = (left + dbCos(angy))*0.9; forw = (forw - dbSin(angy))*0.9; } //O
		if (dbKeyState(37)) { left = (left + dbCos(angy))*0.8; forw = (forw - dbSin(angy))*0.8; } //K
		if (dbKeyState(25)) { left = (left - dbCos(angy))*0.9; forw = (forw + dbSin(angy))*0.9; } //P
		if (dbKeyState(38)) { left = (left - dbCos(angy))*0.8; forw = (forw + dbSin(angy))*0.8; } //L
		if (dbKeyState(23)) { left = (left - dbSin(angy))*0.9; forw = (forw - dbCos(angy))*0.9; } //I
		if (dbKeyState(36)) { left = (left - dbSin(angy))*0.8; forw = (forw - dbCos(angy))*0.8; } //J
		if (dbKeyState(22)) { left = (left + dbSin(angy))*0.9; forw = (forw + dbCos(angy))*0.9; } //U
		if (dbKeyState(35)) { left = (left + dbSin(angy))*0.8; forw = (forw + dbCos(angy))*0.8; } //W

		//if (dbKeyState(22) || dbKeyState(23) || dbKeyState(24) || dbKeyState(25) ){left *= 0.9;forw *= 0.9;}
		//if (dbKeyState(35) || dbKeyState(36) || dbKeyState(37) || dbKeyState(38) ){left *= 0.8;forw *= 0.8;}
		//if (dbKeyState(24) || dbKeyState(25) ){left *= 0.9;}
		//if (dbKeyState(37) || dbKeyState(38) ){left *= 0.8;}
		//if (dbKeyState(22) || dbKeyState(22) ){forw *= 0.9;}
		//if (dbKeyState(35) || dbKeyState(36) ){forw *= 0.8;}

		if (dbControlKey()) 
		{
			forw = 0;
			left = 0;
			down = 0;
			gravi = 0;
			if (sound)
			{
				dbPlaySound(52);
				sound = false;
			}
			if (!(dbSoundPlaying(52)))
			{
				if(boostsound)
				{
					dbLoopSound(53);
					boostsound = false;
				}
			}
			if (dbKeyState(32) || dbRightKey() ) { boostL += left + dbCos(angy); boostF += forw - dbSin(angy); }
			if (dbKeyState(30) || dbLeftKey() ) { boostL += left - dbCos(angy); boostF += forw + dbSin(angy); }
			if (dbKeyState(31) || dbDownKey() ) { boostL += left - dbSin(angy); boostF += forw - dbCos(angy); }
			if (dbKeyState(17) || dbUpKey() ) { boostL += left + dbSin(angy); boostF += forw + dbCos(angy); }
		}
		if (!(dbControlKey()))
		{
			dbStopSound(53);
			if ( (boostL>0) || (boostF>0))
			{
				dbPlaySound(54);
			}
			sound = true;
			boostsound = true;
			forw += boostF;
			boostF = 0;
			left += boostL;
			boostL = 0;
			
		}

		if (dbSpaceKey() && ground)
		{
			down += jump;
			dbPlaySound(51);
		}




		

		
		forw *= 0.95;
		left *= 0.95;

		if (down>0){down *= 0.89;}
		down -= gravi;

		//Kollision Boden
		int collide = SC_SphereSlideGroup( 2, x, y, z, x, y + down, z, radius, 0);

		if(collide >0)
		{
			bounce = down * (-0.75);

			if (bounce >3 || bounce <0){down *= (-0.75); dbPlaySound(50);}
			
			gravi = 0;
			ground = true;
			ny = SC_GetCollisionSlideY()+0.2;
		}
		else
		{
			gravi = gravitation;
			ny = y+down;
			if (down<0) (gravi+=0.2);
			ground = false;		
		}

		collide = SC_SphereSlideGroup( 2, x, y, z, x+left, y, z+forw, radius, 0);
		if (collide > 0)
		{
			
			nx = SC_GetCollisionSlideX();
			nz = SC_GetCollisionSlideZ();
			// kollision vorne oder hinten
			int collide1 = SC_SphereSlideGroup(2, x,y,z, x,y,z+forw,radius,0);
			// kollision seitlicher wand
			int collide2 = SC_SphereSlideGroup(2, x,y,z, x+left,y,z,radius,0);

			if (collide1>0){ forw *= (-0.5); dbPlaySound(50);}  
			if (collide2>0){ left *= (-0.5); dbPlaySound(50);}

			
		}
		else
		{
		nx = x+left;
		nz = z+forw;
		}


		dbPositionObject(1,nx,ny,nz);
		SC_UpdateObject(1);
}
}



void DarkGDK ( void )
{
	dbSyncOn   ( );
	dbSyncRate ( 60 );
	SC_Start();
	dbLoadSound("Media/Sounds/background.wav",60);
	dbLoadSound("Media/Sounds/begin.wav",61);

	while ( LoopGDK ( ) )
	{
		if (soundStart)
		{
			dbPlaySound(61);
			soundStart = false;
		}
		if (!dbSoundPlaying(61) && soundPlaying)
		{
			dbLoopSound(60);
			soundPlaying = false;
		}
		if (selectMode)
		{

			LevelSelect();
			cam = level;
		}
		else
		{
		Menu();

		}
		if (Ingame)
		{
			
			switch(level)
			{
			case 0:
					isDead();
					DelSpritesSelect();
					break;
			case 1: OpenDoor();
					isDead();
					ButtonPressed();
					Finish1();
					DelSpritesSelect();
					break;
			case 2:	isDead();
					Finish2();
					DelSpritesSelect();
					break;
			case 3:
					DelSpritesSelect();
					isDead();
					break;
			default:
					isDead();
					Finish2();
					DelSpritesSelect();
					break;
			}
			MovePlayer();
		}
		else
		{
			switch(level)
			{
			case 1:	DeloadMap1();
					DeloadPlayer();
					break;
			case 2:	DeloadMap2();
					DeloadPlayer();
					break;
			case 4:
					DeloadMap4();
					DeloadPlayer();
					break;
			case 5: 
					DeloadMap4();
					DeloadPlayer();
			case 6:
					DeloadMap4();
					DeloadPlayer();
					break;
			default:
					DeloadMap0();					
			}
		}

		dbSync ( );
	}

	return;
}