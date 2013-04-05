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
GtkWidget *soilImage;

//Levels
int oxygenLvl = 5;
int carbonLvl = 35;
int phosphorusLvl = 15;
int nitrogenLvl = 40;
int waterLvl = 80;

//Statistics
int clover = 0;
int thorn = 0;
int rye = 0;
int sumac = 0;
int bearberry = 0;
int salvia = 0;
int alder = 0;
int dogwood = 0;
int willow = 0;
int till = 0;
int water = 0;
int plow = 0;
int numberTurns = 0;
int numberActions = 0;
int turnCountdown = 50;

//Buffers that can carry 4 digit numbers
char oxygenBuf[4];
char carbonBuf[4];
char phosphorusBuf[4];
char nitrogenBuf[4];
char waterBuf[4];
char cloverBuf[4];
char thornBuf[4];
char ryeBuf[4];
char sumacBuf[4];
char bearberryBuf[4];
char salviaBuf[4];
char alderBuf[4];
char dogwoodBuf[4];
char willowBuf[4];
char tillBuf[4];
char waterBuf[4];
char plowBuf[4];
char turnsBuf[4];
char actionsBuf[4];
char countdownBuf[4];

//Entries for the Text Views
gchar *statsEntry;
gchar *tipEntry1;
gchar *tipEntry2;
gchar *tipEntry3;

//Image path
gchar *imagePath = "src/crappy_soil.jpg";

//Number of "job" selections the player has made 
int numChoices = 0;

//If a certain plant is picked
int pickedClover = 0;
int pickedThorn = 0;
int pickedRye = 0;
int pickedSumac = 0;
int pickedBearberry = 0;
int pickedSalvia = 0;
int pickedAlder = 0;
int pickedDogwood = 0;
int pickedWillow = 0;
int pickedTill = 0;
int pickedWater = 0;
int pickedPlow = 0;

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
		if(strcmp(gtk_button_get_label(GTK_BUTTON(widget)),"Crimson\nClover")==0){
			pickedClover = 1;
		}
		if(strcmp(gtk_button_get_label(GTK_BUTTON(widget)),"Boxthorn")==0){
			pickedThorn = 1;
		}
		if(strcmp(gtk_button_get_label(GTK_BUTTON(widget)),"Rye")==0){
			pickedRye = 1;
		}
		if(strcmp(gtk_button_get_label(GTK_BUTTON(widget)),"Smooth\nSumac")==0){
			pickedSumac = 1;
		}
		if(strcmp(gtk_button_get_label(GTK_BUTTON(widget)),"Bearberry")==0){
			pickedBearberry = 1;
		}
		if(strcmp(gtk_button_get_label(GTK_BUTTON(widget)),"Salvia")==0){
			pickedSalvia = 1;
		}
		if(strcmp(gtk_button_get_label(GTK_BUTTON(widget)),"Alder")==0){
			pickedAlder = 1;
		}
		if(strcmp(gtk_button_get_label(GTK_BUTTON(widget)),"Dogwood")==0){
			pickedDogwood = 1;
		}
		if(strcmp(gtk_button_get_label(GTK_BUTTON(widget)),"Willow")==0){
			pickedWillow = 1;
		}
		if(strcmp(gtk_button_get_label(GTK_BUTTON(widget)),"Till")==0){
			pickedTill = 1;
		}
		if(strcmp(gtk_button_get_label(GTK_BUTTON(widget)),"Water")==0){
			pickedWater = 1;
		}
		if(strcmp(gtk_button_get_label(GTK_BUTTON(widget)),"Plow")==0){
			pickedPlow = 1;
		}

		numChoices++;
	} 

	else {
		/* If control reaches here, the toggle button is up */
		//printf("GTKWidget %s is up \n", gtk_button_get_label (GTK_BUTTON(widget)));

		/*Change variable 'picked' to false*/
		if(strcmp(gtk_button_get_label(GTK_BUTTON(widget)),"Crimson\nClover")==0){
			pickedClover = 0;
		}
		if(strcmp(gtk_button_get_label(GTK_BUTTON(widget)),"Boxthorn")==0){
			pickedThorn = 0;
		}
		if(strcmp(gtk_button_get_label(GTK_BUTTON(widget)),"Rye")==0){
			pickedRye = 0;
		}
		if(strcmp(gtk_button_get_label(GTK_BUTTON(widget)),"Smooth\nSumac")==0){
			pickedSumac = 0;
		}
		if(strcmp(gtk_button_get_label(GTK_BUTTON(widget)),"Bearberry")==0){
			pickedBearberry = 0;
		}
		if(strcmp(gtk_button_get_label(GTK_BUTTON(widget)),"Salvia")==0){
			pickedSalvia = 0;
		}
		if(strcmp(gtk_button_get_label(GTK_BUTTON(widget)),"Alder")==0){
			pickedAlder = 0;
		}
		if(strcmp(gtk_button_get_label(GTK_BUTTON(widget)),"Dogwood")==0){
			pickedDogwood = 0;
		}
		if(strcmp(gtk_button_get_label(GTK_BUTTON(widget)),"Willow")==0){
			pickedWillow = 0;
		}
		if(strcmp(gtk_button_get_label(GTK_BUTTON(widget)),"Till")==0){
			pickedTill = 0;
		}
		if(strcmp(gtk_button_get_label(GTK_BUTTON(widget)),"Water")==0){
			pickedWater = 0;
		}
		if(strcmp(gtk_button_get_label(GTK_BUTTON(widget)),"Plow")==0){
			pickedPlow = 0;
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
				//printf("You chose %d actions \n", numChoices);

				//Display choices the user made
				if(pickedClover){
					printf("You chose Crimson Clover \n");
					oxygenLvl = oxygenLvl + 5;
					clover++;
				}
				if(pickedThorn){
					printf("You chose Boxthorn \n");
					phosphorusLvl = phosphorusLvl + 10;
					thorn++;
				}
				if(pickedRye){
					printf("You chose Rye \n");
					carbonLvl = carbonLvl + 5;
					rye++;
				}
				if(pickedSumac){
					printf("You chose Smooth Sumac \n");
					nitrogenLvl = nitrogenLvl + 15;
					sumac++;
				}
				if(pickedBearberry){
					printf("You chose Bearberry \n");
					nitrogenLvl = nitrogenLvl - 10;
					bearberry++;
				}
				if(pickedSalvia){
					printf("You chose Salvia \n");
					oxygenLvl = oxygenLvl - 5;
					salvia++;
				}
				if(pickedAlder){
					printf("You chose Alder \n");
					waterLvl = waterLvl + 5;
					alder++;
				}
				if(pickedDogwood){
					printf("You chose Dogwood \n");
					phosphorusLvl = phosphorusLvl - 5;
					dogwood++;
				}
				if(pickedWillow){
					printf("You chose Willow \n");
					water = water - 10;
					willow++;
				}
				if(pickedTill){
					printf("You chose Till \n");
					carbonLvl = carbonLvl - 10;
					till++;
				}
				if(pickedWater){
					printf("You chose Water \n");
					water = water + 10;
					water++;
				}
				if(pickedPlow){
					printf("You chose Plow  \n");
					oxygenLvl = oxygenLvl + 10;
					plow++;
				}

				turnCountdown = turnCountdown - 1;
				numberActions = numberActions + numChoices;
				numberTurns++;
				break;

				//Cancel Button was Pressed
			case GTK_RESPONSE_CANCEL:
				printf("Action canceled \n");
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
		sprintf(cloverBuf, "%d", clover);
		sprintf(thornBuf, "%d", thorn);
		sprintf(ryeBuf, "%d", rye);
		sprintf(sumacBuf, "%d", sumac);
		sprintf(bearberryBuf, "%d", bearberry);
		sprintf(salviaBuf, "%d", salvia);
		sprintf(alderBuf, "%d", alder);
		sprintf(dogwoodBuf, "%d", dogwood);
		sprintf(willowBuf, "%d", willow);
		sprintf(tillBuf, "%d", till);
		sprintf(waterBuf, "%d", water);
		sprintf(plowBuf, "%d", plow);
		sprintf(turnsBuf, "%d", numberTurns);
		sprintf(actionsBuf, "%d", numberActions);

		//The text displayed in Stats
		statsEntry = g_strconcat("\t\tStats\n\n\
	Levels\n\
	\tOxygen: ", oxygenBuf, "\n\
	\tCarbon: ", carbonBuf, "\n\
	\tPhosphorus: ", phosphorusBuf,"\n\
	\tNitrogen: ", nitrogenBuf,"\n\
	\tWater: ", waterBuf,"\n\n\
	Plants\n\
	\tCrimson Clover: ", cloverBuf,"\n\
	\tBoxthorn: ", thornBuf,"\n\
	\tRye: ", ryeBuf,"\n\
	\tSmooth Sumac: ", sumacBuf,"\n\
	\tBearberry: ", bearberryBuf,"\n\
	\tSalvia: ", salviaBuf,"\n\n\
	Foliage\n\
	\tAlder: ", alderBuf,"\n\
	\tDogwood: ", dogwoodBuf,"\n\
	\tWillow: ", willowBuf,"\n\n\
	Farming\n\
	\tTill: ", tillBuf,"\n\
	\tWater: ", waterBuf,"\n\
	\tPlow: ", plowBuf,"\n\n\
	Misc\n\
	\tTurns Done: ", turnsBuf,"\n\
	\tActions Done: ", actionsBuf,"\n", NULL);

		gtk_text_buffer_set_text (buffer3,statsEntry,-1);

		/*Update Turns Left*/
		turnsLeft = GTK_WIDGET(gtk_builder_get_object(builder,"labelTurns"));
		sprintf(countdownBuf, "%d turn countdown", turnCountdown);
		gtk_label_set_text(GTK_LABEL(turnsLeft), countdownBuf);
		//gtk_label_set_label(GTK_LABEL(turnsLeft), countdownBuf);

		/*Image for Soil View*/
		if(turnCountdown<48){
			printf("here cd: %d \n",turnCountdown);
			imagePath = "src/nice_soil.jpg";
			soilImage = GTK_WIDGET(gtk_builder_get_object(builder, "image1"));
			soilImage = gtk_image_new_from_file (imagePath);
			gtk_image_set_from_file (GTK_IMAGE (soilImage), imagePath);
			
			gtk_widget_show_all(GTK_WIDGET(soilImage));

		}
		else if(turnCountdown<49){
			printf("HERE COUNTDOWN: %d \n",turnCountdown);
			imagePath = "src/ok_soil.jpg";
			soilImage = GTK_WIDGET(gtk_builder_get_object(builder, "image1"));
			gtk_image_set_from_file (GTK_IMAGE (soilImage), imagePath);

		}

		GValue value = {0,};
		g_value_init (&value, G_TYPE_STRING);

		g_object_get_property(G_OBJECT(soilImage), "file", &value);
		printf("\nFilename = %s\n", g_value_get_string(&value));

		gtk_widget_show_all (GTK_WIDGET (window3));
		gtk_widget_hide (GTK_WIDGET (window2));
		
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
	soilImage = GTK_WIDGET(gtk_builder_get_object(builder, "image1"));
	gtk_image_set_from_file (GTK_IMAGE (soilImage), imagePath);
			
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
	sprintf(cloverBuf, "%d", clover);
	sprintf(thornBuf, "%d", thorn);
	sprintf(ryeBuf, "%d", rye);
	sprintf(sumacBuf, "%d", sumac);
	sprintf(bearberryBuf, "%d", bearberry);
	sprintf(salviaBuf, "%d", salvia);
	sprintf(alderBuf, "%d", alder);
	sprintf(dogwoodBuf, "%d", dogwood);
	sprintf(willowBuf, "%d", willow);
	sprintf(tillBuf, "%d", till);
	sprintf(waterBuf, "%d", water);
	sprintf(plowBuf, "%d", plow);
	sprintf(turnsBuf, "%d", numberTurns);
	sprintf(actionsBuf, "%d", numberActions);

	//The text displayed in Stats
	statsEntry = g_strconcat("\t\tStats\n\n\
	Levels\n\
	\tOxygen: ", oxygenBuf, "\n\
	\tCarbon: ", carbonBuf, "\n\
	\tPhosphorus: ", phosphorusBuf,"\n\
	\tNitrogen: ", nitrogenBuf,"\n\
	\tWater: ", waterBuf,"\n\n\
	Plants\n\
	\tCrimson Clover: ", cloverBuf,"\n\
	\tBoxthorn: ", thornBuf,"\n\
	\tRye: ", ryeBuf,"\n\
	\tSmooth Sumac: ", sumacBuf,"\n\
	\tBearberry: ", bearberryBuf,"\n\
	\tSalvia: ", salviaBuf,"\n\n\
	Foliage\n\
	\tAlder: ", alderBuf,"\n\
	\tDogwood: ", dogwoodBuf,"\n\
	\tWillow: ", willowBuf,"\n\n\
	Farming\n\
	\tTill: ", tillBuf,"\n\
	\tWater: ", waterBuf,"\n\
	\tPlow: ", plowBuf,"\n\n\
	Misc\n\
	\tTurns Done: ", turnsBuf,"\n\
	\tActions Done: ", actionsBuf,"\n", NULL);

	gtk_text_buffer_insert(buffer3, &iter3, statsEntry, -1);

	/*Text View for Almanac Tab*/
	GtkWidget *almanac = GTK_WIDGET(gtk_builder_get_object(builder,"textview3"));
	GtkTextBuffer *buffer;
	GtkTextIter iter;
	buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(almanac));
	gtk_text_buffer_get_iter_at_offset(buffer, &iter, 0);
	const gchar *almanacEntry= "\tCrimson Clover: Crimson clover is widely grown as a protein-rich forage crop for cattle and other livestock. It can typically be found in forest margins, fields and roadsides\n\
	\tBoxthorn: In his Naturalis historia, Pliny the Elder describes boxthorn as a medicinal plant recommended as a treatment for sore eyes and inflammation\n\
	\tRye: Rye is a grass grown extensively as a grain and as a forage crop. It is a member of the wheat tribe (Triticeae) and is closely related to barley (Hordeum) and wheat (Triticum)\n\
	\tSmooth Sumac: Smooth Sumac has a spreading, open-growing shrub growing up to 3 metres (9.8 ft) tall, rarely to 5 metres (16 ft)\n\
	\tBearberry: The leaves are picked any time during the summer and dried for use in infusions, liquid extracts, medicinal tea bags and tablets believed to be potentially effective in folk medicine.\n\
	\tSalvia: Salvia divinorum (also known by its genus name Salvia) is a psychoactive plant which can induce dissociative effects and is a potent producer of visions and other hallucinatory experiences\n\
	\tAlder: Alder is particularly noted for its important symbiotic relationship with Frankia alni, an actinomycete, filamentous, nitrogen-fixing bacterium\n\
	\tDogwood: Dogwoods are widely planted horticulturally, and the dense wood of the larger-stemmed species is valued for certain specialized purposes\n\
	\tWillow: Willows are often planted on the borders of streams so their interlacing roots may protect the bank against the action of the water\n";

	gtk_text_buffer_insert(buffer, &iter, almanacEntry, -1);

	/*Text View for Tip Tab*/
	GtkWidget *tip = GTK_WIDGET(gtk_builder_get_object(builder,"textview2"));
	GtkTextBuffer *buffer2;
	GtkTextIter iter2;
	buffer2 = gtk_text_view_get_buffer(GTK_TEXT_VIEW(tip));
	gtk_text_buffer_get_iter_at_offset(buffer2, &iter2, 0);

	tipEntry1 = "\tTip 1: Your oxygen levels are really low!\
	Consider planting more of Salvia or Crimson Clover to raise your level.\n\n";

	tipEntry2 = "\tTip 2: You're doing a great job with your nitrogen levels.\
	You probably won't need to worry about it for a while\n\n";

	tipEntry3 = "\tTip 3: Your water levels are really high!\
	You might want to plant Willow to lower your level.\n";

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