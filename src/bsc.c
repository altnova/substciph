#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>

#include "___.h"
#include "cfg.h"

#include "min.h"
#include "map.h"
#include "usr.h"
#include "pnt.h"

extern coor crd;

C LINE[] = "Vs lbh nfxrq Oehpr Fpuarvre gb qrpelcg guvf, ur'q pehfu lbhe fxhyy jvgu uvf ynhtu.";


C MAP = 0;

I ST = 2;
I IM;
C IM_S = 0;
I H_ = 0;

C USER_INPUT[US_IN_LEN];
C alphabet[LETTERS];			
S importants[100];

pCoors coors = {4, 3, 7, 6, 0, 17, 0, 18};
coor crd = &coors;


//< alphabet[num] -- key for num letetr 

// enum STATES {quit, help, cc, map, hide};


/****************************************
 *	texttexttexttexttexttext			*
 *										*
 *	a b c d e f g h i j k l m 			*
 *	k k k k k k k k k k k k k 			*
 *										*
 *	n o p q r s t u v w x y z 			*
 *	k k k k k k k k k k k k k 			*
 *										*
 *	::_									*
 *	[error_line]						*
 ****************************************/
/*
///////////////////////////////////////////////////
	typedef struct Coors {
			UH line_x;			//< 4
			UH line_y;			//< 0
			UH map_x;			//<	6
			UH map_y;			//<	3
			UH usr_x;			//<	4
			UH usr_y;			//<	9
	} pCoors;
	typedef pCoors* coors;

	pCoors coor = {4, 0, 6, 3, 4, 12};
	coors crd = &coor;
///////////////////////////////////////////////////

	#define gotoxy(x,y) printf("\033[%d;%dH",(x),(y))
	#define clrscr() printf("\e[1;1H\e[2J");

	#define US_IN_LEN 10
///////////////////////////////////////////////////
	S LINE = "Vs lbh nfxrq Oehpr Fpuarvre gb qrpelcg guvf, ur'q pehfu lbhe fxhyy jvgu uvf ynhtu."
	C USER_INPUT[US_IN_LEN];
	I ST = 0;

	enum ATOZ {A_, B_, C_, D_, E_, F_, G_, H_, I_, J_, K_, L_, M_, N_, O_, P_, Q_, R_, S_, T_, U_, V_, W_, X_, Y_, Z_};
	C alphabet[26];			

	//< alphabet[num] -- key for num letetr 

	enum STATES {quit, help, cc, map, hide};
///////////////////////////////////////////////////
*/
//<	states
//<	0: 	! 		help
//<	1: 	q 		quit
//<	2: 	cc		decrypt
//<	3:	m 		map
//<	4:	h 		hide map

V process()
{
	while (ST != quit) {
		user_input(USER_INPUT, US_IN_LEN); 				//< get user's input; 
		clear_error();
		ST = input_state(USER_INPUT);			//< calculates state type from USER_INPUT

		SW(ST) { 
			CS(help,{	MAP = 0; show_help();});	
			CS(cc, 	{	upd_cph(LINE, USER_INPUT, LEN, alphabet);});
			CS(lght,{	highlighted_line(LINE, USER_INPUT + 1);});
			CS(map, {	MAP = 1; IM_S = 0; show_map(alphabet);});
			CS(hide,{	IM_S = 0; MAP = 0; hide_map();});
			CS(imp,	{	IM_S = 1; MAP = 0; show_importants(importants, alphabet);});
			
			CS(quit,{	break;});
			CD: 		error_message("invalid command", 0, "");
		}
	}

}


I main()
{
	I i;
	clrscr();
	
	mod_line(LINE, "vv", LEN, alphabet);
	make_map(LINE, alphabet);
	count_importants(LINE, LEN, importants);
	show_help();

	process();
	result(alphabet);
	getchar();
	clrscr();
	return 0;
}





