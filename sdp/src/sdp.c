/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * sdp.c
 * Copyright (C) Kevin Welsh 2012 <kcwelsh@mtu.edu>, <welshk91@gmail.com>
	 * 
 * sdp is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
	 * 
 * sdp is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include "sdp.h"
#include <stdio.h>
#include <stdlib.h>
#include <glib/gi18n.h>

/* For testing propose use the local (not installed) ui file */
/* #define UI_FILE PACKAGE_DATA_DIR"/sdp/ui/title.ui" */
#define UI_TITLE "src/title.ui"
#define UI_STORY "src/story.ui"
#define UI_STATUS "src/status.ui"

//Top level windows used in each screen
GtkWidget *window;
GtkWidget *window2;
GtkWidget *window3;

//Needed to update Stats page and turn label
GtkTextBuffer *buffer3;
GtkWidget *stats;
GtkWidget *turnsLeft;
GtkTextIter iter3;

//Levels
int oxygenLvl = 5;
int carbonLvl = 35;
int phosphorusLvl = 15;
int nitrogenLvl = 40;
int waterLvl = 80;

//Statistics
int plantA = 0;
int plantB = 0;
int plantC = 0;
int plantD = 0;
int plantE = 0;
int plantF = 0;
int numberTurns = 0;
int numberActions = 0;
int turnCountdown = 50;

//Buffers that can carry 4 digit numbers
char oxygenBuf[4];
char carbonBuf[4];
char phosphorusBuf[4];
char nitrogenBuf[4];
char waterBuf[4];
char aBuf[4];
char bBuf[4];
char cBuf[4];
char dBuf[4];
char eBuf[4];
char fBuf[4];
char turnsBuf[4];
char actionsBuf[4];
char countdownBuf[4];

//Entries for the Text Views
gchar *statsEntry;
gchar *tipEntry1;
gchar *tipEntry2;
gchar *tipEntry3;

//Number of "job" selections the player has made 
int numChoices = 0;

//If a certain plant is picked
int pickedA = 0;
int pickedB = 0;
int pickedC = 0;
int pickedD = 0;
int pickedE = 0;
int pickedF = 0;
int pickedG = 0;
int pickedH = 0;
int pickedI = 0;
int pickedJ = 0;
int pickedK = 0;
int pickedL = 0;

G_DEFINE_TYPE (Sdp, sdp, GTK_TYPE_APPLICATION);


//Method for Exiting
static void exitTime (void)
{
	exit(0);
}

//Method for Toggle Buttons to listen for clicks
void toggle_button_callback (GtkWidget *widget, gpointer data)
{

	if (gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON (widget))) {
		/* If control reaches here, the toggle button is down */
		//printf("GTKWidget %s is down \n", gtk_button_get_label (GTK_BUTTON(widget)));

		/*Change variable 'picked' to true*/
		if(strcmp(gtk_button_get_label(GTK_BUTTON(widget)),"Plant A")==0){
			pickedA = 1;
		}
		if(strcmp(gtk_button_get_label(GTK_BUTTON(widget)),"Plant B")==0){
			pickedB = 1;
		}
		if(strcmp(gtk_button_get_label(GTK_BUTTON(widget)),"Plant C")==0){
			pickedC = 1;
		}
		if(strcmp(gtk_button_get_label(GTK_BUTTON(widget)),"Plant D")==0){
			pickedD = 1;
		}
		if(strcmp(gtk_button_get_label(GTK_BUTTON(widget)),"Plant E")==0){
			pickedE = 1;
		}
		if(strcmp(gtk_button_get_label(GTK_BUTTON(widget)),"Plant F")==0){
			pickedF = 1;
		}
		if(strcmp(gtk_button_get_label(GTK_BUTTON(widget)),"Trees")==0){
			pickedG = 1;
		}
		if(strcmp(gtk_button_get_label(GTK_BUTTON(widget)),"Bushes")==0){
			pickedH = 1;
		}
		if(strcmp(gtk_button_get_label(GTK_BUTTON(widget)),"???")==0){
			pickedI = 1;
		}
		if(strcmp(gtk_button_get_label(GTK_BUTTON(widget)),"Toil")==0){
			pickedJ = 1;
		}
		if(strcmp(gtk_button_get_label(GTK_BUTTON(widget)),"Water")==0){
			pickedK = 1;
		}
		if(strcmp(gtk_button_get_label(GTK_BUTTON(widget)),"?????")==0){
			pickedL = 1;
		}

		numChoices++;
	} 

	else {
		/* If control reaches here, the toggle button is up */
		//printf("GTKWidget %s is up \n", gtk_button_get_label (GTK_BUTTON(widget)));

		/*Change variable 'picked' to false*/
		if(strcmp(gtk_button_get_label(GTK_BUTTON(widget)),"Plant A")==0){
			pickedA = 0;
		}
		if(strcmp(gtk_button_get_label(GTK_BUTTON(widget)),"Plant B")==0){
			pickedB = 0;
		}
		if(strcmp(gtk_button_get_label(GTK_BUTTON(widget)),"Plant C")==0){
			pickedC = 0;
		}
		if(strcmp(gtk_button_get_label(GTK_BUTTON(widget)),"Plant D")==0){
			pickedD = 0;
		}
		if(strcmp(gtk_button_get_label(GTK_BUTTON(widget)),"Plant E")==0){
			pickedE = 0;
		}
		if(strcmp(gtk_button_get_label(GTK_BUTTON(widget)),"Plant F")==0){
			pickedF = 0;
		}
		if(strcmp(gtk_button_get_label(GTK_BUTTON(widget)),"Trees")==0){
			pickedG = 0;
		}
		if(strcmp(gtk_button_get_label(GTK_BUTTON(widget)),"Bushes")==0){
			pickedH = 0;
		}
		if(strcmp(gtk_button_get_label(GTK_BUTTON(widget)),"???")==0){
			pickedI = 0;
		}
		if(strcmp(gtk_button_get_label(GTK_BUTTON(widget)),"Toil")==0){
			pickedJ = 0;
		}
		if(strcmp(gtk_button_get_label(GTK_BUTTON(widget)),"Water")==0){
			pickedK = 0;
		}
		if(strcmp(gtk_button_get_label(GTK_BUTTON(widget)),"?????")==0){
			pickedL = 0;
		}

		numChoices--;
	}

	//printf("COUNT:%d \n", numChoices);

}

//Method for Accept
static void acceptTime (void)
{

	GtkBuilder *builder;
	GError* error = NULL;

	// Load UI from file
	builder = gtk_builder_new ();
	if (!gtk_builder_add_from_file (builder, UI_STATUS, &error))
	{
		g_critical ("Couldn't load builder file: %s", error->message);
		g_error_free (error);
	}

	// Auto-connect signal handlers /
	gtk_builder_connect_signals (builder, NULL);

	//You picked too many choices for a turn
	if(numChoices>2){

		/* Auto-connect signal handlers */
		gtk_builder_connect_signals (builder, NULL);

		GtkWidget *dialog;
		dialog = gtk_message_dialog_new (GTK_WINDOW(gtk_builder_get_object(builder,"window1")),
		                                 GTK_DIALOG_DESTROY_WITH_PARENT,
		                                 GTK_MESSAGE_ERROR,
		                                 GTK_BUTTONS_CLOSE,    
		                                 "You picked too many choices for a single turn!\nYou can only pick two.");
		gtk_dialog_run (GTK_DIALOG (dialog));
		gtk_widget_destroy (dialog);

	}

	//You picked too few choices
	else if(numChoices<2){
		/* Auto-connect signal handlers */
		gtk_builder_connect_signals (builder, NULL);

		GtkWidget *dialog;
		dialog = gtk_message_dialog_new (GTK_WINDOW(gtk_builder_get_object(builder,"window1")),
		                                 GTK_DIALOG_DESTROY_WITH_PARENT,
		                                 GTK_MESSAGE_ERROR,
		                                 GTK_BUTTONS_CLOSE,    
		                                 "You picked too few choices for a single turn!\nYou can only pick two.");
		gtk_dialog_run (GTK_DIALOG (dialog));
		gtk_widget_destroy (dialog);
		
	}

	//You picked the right amount
	else{

		/* Create the dialog confirmation box */
		GtkWidget *dialog, *label, *contentArea;
		dialog = gtk_dialog_new_with_buttons ("Confirm Choice...",
		                                      GTK_WINDOW(gtk_builder_get_object(builder,"window3")),
		                                      GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT,
		                                      GTK_STOCK_CANCEL,
		                                      GTK_RESPONSE_CANCEL,
		                                      GTK_STOCK_OK,
		                                      GTK_RESPONSE_OK,
		                                      NULL);
		contentArea = gtk_dialog_get_content_area (GTK_DIALOG (dialog));
		label = gtk_label_new ("Are you sure you wish to continue?\n");

		/* Add the label, and show everything we've added to the dialog. */
		gtk_container_add (GTK_CONTAINER (contentArea), label);
		gtk_widget_show(contentArea);
		gtk_widget_show(label);
		gint dialogResult = gtk_dialog_run (GTK_DIALOG(dialog));

		/*Handle dialog decisions*/
		switch(dialogResult){

			//Accept Button was Pressed
			case GTK_RESPONSE_OK:
				printf("You chose %d actions \n", numChoices);

				//Display choices the user made
				if(pickedA){
					printf("You chose Plant A \n");
					oxygenLvl = oxygenLvl + 5;
					plantA++;
				}
				if(pickedB){
					printf("You chose Plant B \n");
					phosphorusLvl = phosphorusLvl + 10;
					plantB++;
				}
				if(pickedC){
					printf("You chose Plant C \n");
					carbonLvl = carbonLvl + 5;
					plantC++;
				}
				if(pickedD){
					printf("You chose Plant D \n");
					nitrogenLvl = nitrogenLvl + 15;
					plantD++;
				}
				if(pickedE){
					printf("You chose Plant E \n");
					waterLvl = waterLvl + 5;
					plantE++;
				}
				if(pickedF){
					printf("You chose Plant F \n");
					oxygenLvl = oxygenLvl + 10;
					plantF++;
				}
				if(pickedG){
					printf("You chose Trees \n");
					waterLvl = waterLvl + 5;
					//plantG++;
				}
				if(pickedH){
					printf("You chose Bushes \n");
					phosphorusLvl = phosphorusLvl - 5;
					//plantH++;
				}
				if(pickedI){
					printf("You chose ??? \n");
					carbonLvl = carbonLvl - 10;
					//plantI++;
				}
				if(pickedJ){
					printf("You chose Toil \n");
					waterLvl = waterLvl - 5;
					//plantJ++;
				}
				if(pickedK){
					printf("You chose Water \n");
					nitrogenLvl = nitrogenLvl - 10;
					//plantK++;
				}
				if(pickedL){
					printf("You chose ?????  \n");
					oxygenLvl = oxygenLvl - 5;
					//plantL++;
				}

				turnCountdown = turnCountdown - 1;
				numberActions = numberActions + numChoices;
				numberTurns++;
				break;

				//Cancel Button was Pressed
			case GTK_RESPONSE_CANCEL:
				printf("boo \n");
				exitTime();
				break;

				//Unexpected Response
			default:
				printf("UNEXPECTED DIALOG ERROR\n");
				exit(2);
				break;
		}

		//Destroy Dialog Box after response
		gtk_widget_destroy (label);
		gtk_widget_destroy (contentArea);
		gtk_widget_destroy (dialog);

		/*Update Stats Screen*/
		//Make a string with the integer values
		sprintf(oxygenBuf, "%d", oxygenLvl);
		sprintf(carbonBuf, "%d", carbonLvl);
		sprintf(phosphorusBuf, "%d", phosphorusLvl);
		sprintf(nitrogenBuf, "%d", nitrogenLvl);
		sprintf(waterBuf, "%d", waterLvl);
		sprintf(aBuf, "%d", plantA);
		sprintf(bBuf, "%d", plantB);
		sprintf(cBuf, "%d", plantC);
		sprintf(dBuf, "%d", plantD);
		sprintf(eBuf, "%d", plantE);
		sprintf(fBuf, "%d", plantF);
		sprintf(turnsBuf, "%d", numberTurns);
		sprintf(actionsBuf, "%d", numberActions);

		//The text displayed in Stats
		statsEntry = g_strconcat("\t\tStats\n\n\
	\tLevels\n\
	\tOxygen: ", oxygenBuf, "\n\
	\tCarbon: ", carbonBuf, "\n\
	\tPhosphorus: ", phosphorusBuf,"\n\
	\tNitrogen: ", nitrogenBuf,"\n\
	\tWater: ", waterBuf,"\n\n\
	\tPlants\n\
	\tPlant A: ", aBuf,"\n\
	\tPlant B: ", bBuf,"\n\
	\tPlant C: ", cBuf,"\n\
	\tPlant D: ", dBuf,"\n\
	\tPlant E: ", eBuf,"\n\
	\tPlant F: ", fBuf,"\n\n\
	\tMisc\n\
	\tTurns Done: ", turnsBuf,"\n\
	\tActions Done: ", actionsBuf,"\n", NULL);

		gtk_text_buffer_set_text (buffer3,statsEntry,-1);

		/*Update Turns Left*/
		turnsLeft = GTK_WIDGET(gtk_builder_get_object(builder,"labelTurns"));
		sprintf(countdownBuf, "%d turn countdown", turnCountdown);
		gtk_label_set_text(GTK_LABEL(turnsLeft), countdownBuf);

		printf("COUNTDOWN: %d \n",turnCountdown);

	}

}//end of AcceptTime

//Method for Continue
static void continueTime(void)
{

	GtkBuilder *builder;
	GError* error = NULL;

	/* Load UI from file */
	builder = gtk_builder_new ();
	if (!gtk_builder_add_from_file (builder, UI_STATUS, &error))
	{
		g_critical ("Couldn't load builder file: %s", error->message);
		g_error_free (error);
	}

	/* Auto-connect signal handlers */
	gtk_builder_connect_signals (builder, NULL);

	/*Connect Buttons in UI File with variables*/
	GtkWidget *btnAccept = GTK_WIDGET(gtk_builder_get_object (builder,"buttonAccept"));

	/*Connect Continue button with 'continueTime' function*/
	g_signal_connect(btnAccept,"clicked",G_CALLBACK(acceptTime), NULL);

	/*Image for Soil View*/
	GtkWidget *soilImage = GTK_WIDGET(gtk_builder_get_object(builder, "image1"));
	gtk_image_set_from_file (GTK_IMAGE (soilImage), "src/crappy_soil.jpg");

	/*Turns label*/
	//turnsLeft = GTK_WIDGET(gtk_builder_get_object(builder,"labelTurns"));
	//sprintf(countdownBuf, "%d Turns Left", turnCountdown);
	//gtk_label_set_text(GTK_LABEL(turnsLeft), countdownBuf);


	/*Text View for Almanac Tab*/
	stats = GTK_WIDGET(gtk_builder_get_object(builder,"textview1"));
	buffer3 = gtk_text_view_get_buffer(GTK_TEXT_VIEW(stats));
	gtk_text_buffer_get_iter_at_offset(buffer3, &iter3, 0);

	//Make a string with the integer values
	sprintf(oxygenBuf, "%d", oxygenLvl);
	sprintf(carbonBuf, "%d", carbonLvl);
	sprintf(phosphorusBuf, "%d", phosphorusLvl);
	sprintf(nitrogenBuf, "%d", nitrogenLvl);
	sprintf(waterBuf, "%d", waterLvl);
	sprintf(aBuf, "%d", plantA);
	sprintf(bBuf, "%d", plantB);
	sprintf(cBuf, "%d", plantC);
	sprintf(dBuf, "%d", plantD);
	sprintf(eBuf, "%d", plantE);
	sprintf(fBuf, "%d", plantF);
	sprintf(turnsBuf, "%d", numberTurns);
	sprintf(actionsBuf, "%d", numberActions);

	//The text displayed in Stats
	statsEntry = g_strconcat("\t\tStats\n\n\
	\tLevels\n\
	\tOxygen: ", oxygenBuf, "\n\
	\tCarbon: ", carbonBuf, "\n\
	\tPhosphorus: ", phosphorusBuf,"\n\
	\tNitrogen: ", nitrogenBuf,"\n\
	\tWater: ", waterBuf,"\n\n\
	\tPlants\n\
	\tPlant A: ", aBuf,"\n\
	\tPlant B: ", bBuf,"\n\
	\tPlant C: ", cBuf,"\n\
	\tPlant D: ", dBuf,"\n\
	\tPlant E: ", eBuf,"\n\
	\tPlant F: ", fBuf,"\n\n\
	\tMisc\n\
	\tTurns Done: ", turnsBuf,"\n\
	\tActions Done: ", actionsBuf,"\n", NULL);

	gtk_text_buffer_insert(buffer3, &iter3, statsEntry, -1);


	/*Text View for Almanac Tab*/
	GtkWidget *almanac = GTK_WIDGET(gtk_builder_get_object(builder,"textview3"));
	GtkTextBuffer *buffer;
	GtkTextIter iter;
	buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(almanac));
	gtk_text_buffer_get_iter_at_offset(buffer, &iter, 0);
	const gchar *almanacEntry= "\tPlant 1: This is description for plant one\n\
	\tPlant 2: This is description for plant two\n\
	\tPlant 3: This is description for plant three\n\
	\tPlant 4: This is description for plant four\n\
	\tPlant 5: This is description for plant five\n\
	\tPlant 6: This is description for plant six\n\
	\tPlant 7: This is description for plant seven\n";

	gtk_text_buffer_insert(buffer, &iter, almanacEntry, -1);

	/*Text View for Tip Tab*/
	GtkWidget *tip = GTK_WIDGET(gtk_builder_get_object(builder,"textview2"));
	GtkTextBuffer *buffer2;
	GtkTextIter iter2;
	buffer2 = gtk_text_view_get_buffer(GTK_TEXT_VIEW(tip));
	gtk_text_buffer_get_iter_at_offset(buffer2, &iter2, 0);

	tipEntry1 = "\tTip 1: Your oxygen levels are really low!\
	Consider planting more of plant 3 or plant 7 to raise your level.\n\n";

	tipEntry2 = "\tTip 2: You're doing a great job with your nitrogen levels.\
	You probably won't need to worry about it for a while\n\n";

	tipEntry3 = "\tTip 3: Your water levels are really high!\
	You might want to plant plant 2 to lower your level.\n";

	//Combine Tips together	
	gchar *tipEntry = g_strconcat(tipEntry1,tipEntry2,tipEntry3,NULL);
	gtk_text_buffer_insert(buffer2, &iter2, tipEntry, -1);

	/* Get the window object from the ui file */
	window3 = GTK_WIDGET (gtk_builder_get_object (builder, "window3"));
	if (!window3){
		g_critical ("Widget \"%s\" is missing in file %s.",
		            "window3",
		            UI_STATUS);
	}

	g_object_unref (builder);

	g_free(statsEntry);

	gtk_widget_show_all (GTK_WIDGET (window3));
	gtk_widget_hide (GTK_WIDGET (window2));

}//end of continueTime

//Method for Help
static void helpTime (void)
{

	GtkBuilder *builder;
	GError* error = NULL;

	/* Load UI from file */
	builder = gtk_builder_new ();
	if (!gtk_builder_add_from_file (builder, UI_TITLE, &error))
	{
		g_critical ("Couldn't load builder file: %s", error->message);
		g_error_free (error);
	}

	/* Auto-connect signal handlers */
	gtk_builder_connect_signals (builder, NULL);

	GtkWidget *dialog;
	dialog = gtk_message_dialog_new (GTK_WINDOW(gtk_builder_get_object(builder,"window1")),
	                                 GTK_DIALOG_DESTROY_WITH_PARENT,
	                                 GTK_MESSAGE_ERROR,
	                                 GTK_BUTTONS_CLOSE,    
	                                 "Sorry. This is just a prototype...");
	gtk_dialog_run (GTK_DIALOG (dialog));
	gtk_widget_destroy (dialog);

}

//Method for Options
static void optionTime (void)
{

	GtkBuilder *builder;
	GError* error = NULL;

	/* Load UI from file */
	builder = gtk_builder_new ();
	if (!gtk_builder_add_from_file (builder, UI_TITLE, &error))
	{
		g_critical ("Couldn't load builder file: %s", error->message);
		g_error_free (error);
	}

	/* Auto-connect signal handlers */
	gtk_builder_connect_signals (builder, NULL);

	GtkWidget *dialog;
	dialog = gtk_message_dialog_new (GTK_WINDOW(gtk_builder_get_object(builder,"window1")),
	                                 GTK_DIALOG_DESTROY_WITH_PARENT,
	                                 GTK_MESSAGE_ERROR,
	                                 GTK_BUTTONS_CLOSE,    
	                                 "Sorry. This is just a prototype...");
	gtk_dialog_run (GTK_DIALOG (dialog));
	gtk_widget_destroy (dialog);

}

//Method for Start
static void startTime (void)
{
	GtkBuilder *builder;
	GError* error = NULL;

	/* Load UI from file */
	builder = gtk_builder_new ();
	if (!gtk_builder_add_from_file (builder, UI_STORY, &error))
	{
		g_critical ("Couldn't load builder file: %s", error->message);
		g_error_free (error);
	}

	/* Auto-connect signal handlers */
	gtk_builder_connect_signals (builder, NULL);

	/*Connect Buttons in UI File with variables*/
	GtkWidget *btnContinue = GTK_WIDGET(gtk_builder_get_object (builder,"buttonContinue"));

	/*Connect Continue button with 'continueTime' function*/
	g_signal_connect(btnContinue,"clicked",G_CALLBACK(continueTime), NULL);

	/*Text View for Story Line*/
	GtkWidget *story = GTK_WIDGET(gtk_builder_get_object(builder,"textview1"));
	GtkTextBuffer *buffer;
	GtkTextIter iter;
	buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(story));
	gtk_text_buffer_get_iter_at_offset(buffer, &iter, 0);
	const gchar *storyLine= "\tDear Residence,\n\n \
	You have just inherited a rundown farm from your uncle.\
	The soil is currently in such bad shape that nothing can currently grow.\
	In order to grow crops, you need to nurture the land back to health.\n\n\
	Sincerely,\n\
	Mr.Governor";

	gtk_text_buffer_insert(buffer, &iter, storyLine, -1);



	/* Get the window object from the ui file */
	window2 = GTK_WIDGET (gtk_builder_get_object (builder, "window2"));
	if (!window2)
	{
		g_critical ("Widget \"%s\" is missing in file %s.",
		            "window2",
		            UI_STORY);
	}
	g_object_unref (builder);

	gtk_widget_show_all (GTK_WIDGET (window2));
	gtk_widget_hide (GTK_WIDGET (window));

}//end of startTime

/* Creates the first window of the program, the Title Screen */
static void
sdp_new_window (GApplication *app,
                GFile        *file)
{
	GtkBuilder *builder;
	GError* error = NULL;

	/* Load UI from file */
	builder = gtk_builder_new ();
	if (!gtk_builder_add_from_file (builder, UI_TITLE, &error))
	{
		g_critical ("Couldn't load builder file: %s", error->message);
		g_error_free (error);
	}

	/* Auto-connect signal handlers */
	gtk_builder_connect_signals (builder, NULL);

	/*Connect Buttons in UI File with variables*/
	GtkWidget *btnExit= GTK_WIDGET(gtk_builder_get_object (builder,"buttonExit"));
	GtkWidget *btnHelp= GTK_WIDGET(gtk_builder_get_object (builder,"buttonHelp"));
	GtkWidget *btnOptions= GTK_WIDGET(gtk_builder_get_object (builder,"buttonOptions"));
	GtkWidget *btnStart= GTK_WIDGET(gtk_builder_get_object (builder,"buttonStart"));

	/*Connect Exit button with 'exitTime' function*/
	g_signal_connect(btnExit,"clicked",G_CALLBACK(exitTime), NULL);

	/*Connect Help button with 'helpTime' function*/
	g_signal_connect(btnHelp,"clicked",G_CALLBACK(helpTime), NULL);

	/*Connect Options button with 'optionTime' function*/
	g_signal_connect(btnOptions,"clicked",G_CALLBACK(optionTime), NULL);

	/*Connect Start button with 'startTime' function*/
	g_signal_connect(btnStart,"clicked",G_CALLBACK(startTime), NULL);


	/* Get the window object from the ui file */
	window = GTK_WIDGET (gtk_builder_get_object (builder, "window"));
	if (!window)
	{
		g_critical ("Widget \"%s\" is missing in file %s.",
		            "window",
		            UI_TITLE);
	}
	g_object_unref (builder);

	gtk_window_set_application (GTK_WINDOW (window), GTK_APPLICATION (app));
	if (file != NULL)
	{
		/* TODO: Add code here to open the file in the new window */
	}
	gtk_widget_show_all (GTK_WIDGET (window));
}


/* GApplication implementation */
static void
sdp_activate (GApplication *application)
{
	sdp_new_window (application, NULL);
}

static void
sdp_open (GApplication  *application,
          GFile        **files,
          gint           n_files,
          const gchar   *hint)
{
	gint i;

	for (i = 0; i < n_files; i++)
		sdp_new_window (application, files[i]);
}

static void
sdp_init (Sdp *object)
{

}

static void
sdp_finalize (GObject *object)
{

	G_OBJECT_CLASS (sdp_parent_class)->finalize (object);
}

static void
sdp_class_init (SdpClass *klass)
{
	G_APPLICATION_CLASS (klass)->activate = sdp_activate;
	G_APPLICATION_CLASS (klass)->open = sdp_open;

	G_OBJECT_CLASS (klass)->finalize = sdp_finalize;
}

Sdp *
sdp_new (void)
{
	g_type_init ();

	return g_object_new (sdp_get_type (),
	                     "application-id", "org.gnome.sdp",
	                     "flags", G_APPLICATION_HANDLES_OPEN,
	                     NULL);
}