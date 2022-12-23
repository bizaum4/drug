//cc -o game drug_game.c -lncurses -lmenu && ./game

#include <curses.h>
#include <stdlib.h>
#include <string.h>
#include <menu.h>
#include <unistd.h>
#include <time.h>
#include <sys/time.h>
#include <locale.h>
#define ARRAY_SIZE(a) (sizeof(a) / sizeof(a[0]))

char *product[] = {
  "stuff",
  "cocaine",
  "speed",
  "crystal meth",
  "mescaline",
  "xanax",
  "tramadol",
  "oxicodone",
  "go to deal",
  "exit"
};

char *price[] = {
  "   price",
  "   1 unit - 750 $",
  "   1 unit - 900 $",
  "   1 unit - 2000 $",
  "   1 unit - 800 $",
  "   1 unit - 300 $",
  "   1 unit - 950 $ ",
  "   1 unit - 1800 $",
  "            ",
  "            "
};

int Dealer_Deal ();
int menu ();
int score_amount ();
ITEM **my_items;
int c;
MENU *my_menu;
int n_product, i;
int score = 10000;
int amount = 0;
int deal;
int
score_amount ()
{

  mvprintw (27, 40, "your score  : %d                        ", score);
  mvprintw (29, 40, "your amount : %d                        ", amount);

}

int
menu ()
{
  n_product = ARRAY_SIZE (product);
  my_items = (ITEM **) calloc (n_product + 1, sizeof (ITEM *));
  for (i = 0; i < n_product; ++i)
    {
      my_items[i] = new_item (product[i], price[i]);
    }
  my_items[n_product] = (ITEM *) NULL;
  my_menu = new_menu ((ITEM **) my_items);
  score_amount ();
  set_menu_sub (my_menu, derwin (stdscr, 12, 42, 11, 40));
  set_menu_mark (my_menu, "* ");
  border (ACS_CKBOARD, ACS_CKBOARD, ACS_CKBOARD, ACS_CKBOARD, ACS_CKBOARD,
	  ACS_CKBOARD, ACS_CKBOARD, ACS_CKBOARD);
  post_menu (my_menu);
  refresh ();
}

int
Dealer_Deal ()
{
  time_t tr;
  srand ((unsigned) time (&tr));
  deal = rand () % 10;
  while (amount != 0)
    {
      if (deal == 0)
	{
	  mvprintw (31, 40,
		    "your dealer was killed by an 'unsafe condoms' gang              ");
	  amount = 0;
	  score_amount ();
	}

      if ((deal == 1) || (deal == 3) || (deal == 4) || (deal == 5) || (deal == 7) || (deal == 8))
	{
	  mvprintw (31, 40,
		    "everything went well. you have doubled your investment           ");
	  amount *= 2;
	  score = (score + amount);
	  amount = 0;
	  score_amount ();
	}
      if (deal == 2)
	{
	  mvprintw (31, 40,
		    "your dealer  arrested by the police                               ");
	  amount = 0;
	  score_amount ();
	}
      
      
      
      if (deal == 6)
	{
	  mvprintw (31, 40,
		    "your dealer was drunk and lost the product                            ");
	  amount = 0;
	  score_amount ();
	}
      
      if (deal == 9)
	{
	  mvprintw (31, 40,
		    "your dealer very smart . he multiplied the investment by 7 time");
	  amount *= 7;
	  score = (score + amount);
	  amount = 0;
	  score_amount ();
	}
    }

}
int
main ()
{

  time_t tim;
  struct tm *t;
  char *text;
  struct timeval current;
  double fraction = 0.0;
  setlocale (LC_ALL, "");
  initscr ();
  start_color ();
  assume_default_colors (COLOR_BLACK, COLOR_CYAN);
  cbreak ();
  noecho ();
  keypad (stdscr, TRUE);
  nodelay (stdscr, TRUE);
  curs_set (0);
  mvprintw (2, 0,
	    "          hello !!!  my nane is Nestor.i am a prisoner.some time ago due to my stupidity i ended up in jail.\n"
	    "          local gangs took advantage of my inexperience and dragged me into an unwinnable game. i owe a huge\n"
	    "          amount of one million dollars.if i don't, they'll kill me. i have 10 000 dollars and several free \n"
	    "          dealers .you will be my intermediary.buy and sell to dealers and see how the card falls. good luck\n");
  mvwaddch (stdscr, 7, 0, ACS_CKBOARD);
  hline (ACS_CKBOARD, 140);
  mvwaddch (stdscr, 8, 0, ACS_CKBOARD);
  hline (ACS_CKBOARD, 140);
  mvwaddch (stdscr, 24, 0, ACS_CKBOARD);
  hline (ACS_CKBOARD, 140);
  mvwaddch (stdscr, 25, 0, ACS_CKBOARD);
  hline (ACS_CKBOARD, 140);
  menu ();
  while (c = getch ())
    {
      napms (10);
      tim = time (0);
      t = localtime (&tim);
      gettimeofday (&current, 0);
      text = ctime (&tim);
      mvprintw (10, 3, "%.*s", (int) (strlen (text) - 1), text);
      refresh ();
      switch (c)
	{
	case KEY_DOWN:
	  menu_driver (my_menu, REQ_DOWN_ITEM);
	  break;
	case KEY_UP:
	  menu_driver (my_menu, REQ_UP_ITEM);
	  break;

	case 10:

	  item_name (current_item (my_menu));
	  pos_menu_cursor (my_menu);
	  if (strcmp (item_name (current_item (my_menu)), "cocaine") == 0
	      && (score >= 750))
	    {
	      score -= 750;
	      amount += 750;
	      score_amount ();
	    }

	  if (strcmp (item_name (current_item (my_menu)), "speed") == 0
	      && (score >= 900))
	    {
	      score -= 900;
	      amount += 900;
	      score_amount ();
	    }
	  if (strcmp (item_name (current_item (my_menu)), "crystal meth") == 0
	      && (score >= 2000))
	    {
	      score -= 2000;
	      amount += 2000;
	      score_amount ();
	    }

	  if (strcmp (item_name (current_item (my_menu)), "mescaline") == 0
	      && (score >= 800))
	    {
	      score -= 800;
	      amount += 800;
	      score_amount ();
	    }
	  if (strcmp (item_name (current_item (my_menu)), "xanax") == 0
	      && (score >= 300))
	    {
	      score -= 300;
	      amount += 300;
	      score_amount ();
	    }
	  if (strcmp (item_name (current_item (my_menu)), "tramadol") == 0
	      && (score >= 950))
	    {
	      score -= 950;
	      amount += 950;
	      score_amount ();
	    }
	  if (strcmp (item_name (current_item (my_menu)), "oxicodone") == 0
	      && (score >= 1800))
	    {
	      score -= 1800;
	      amount += 1800;
	      score_amount ();
	    }
	  if (strcmp (item_name (current_item (my_menu)), "exit") == 0)
	    {

	      unpost_menu (my_menu);
	      for (i = 0; i < n_product; ++i)
		free_item (my_items[i]);
	      free_menu (my_menu);
	      endwin ();
	      exit (0);
	    }
	  if (strcmp (item_name (current_item (my_menu)), "go to deal") == 0)
	    {
	      Dealer_Deal ();
	      score_amount ();
	    }

	  if (score >= 1000000)
	    {
	      mvprintw (15, 3,
			"you save me . thanks !!!                                         ");
	      menu ();
	      napms (10000);
	      unpost_menu (my_menu);
	      for (i = 0; i < n_product; ++i)
		free_item (my_items[i]);
	      free_menu (my_menu);
	      endwin ();
	      exit (0);
	    }
            if (amount == 0 && score < 300)
             {
              unpost_menu (my_menu);
	      for (i = 0; i < n_product; ++i)
		free_item (my_items[i]);
	      free_menu (my_menu);
	      endwin ();
	      exit (0);
          }

	  break;
	}
    }
}
