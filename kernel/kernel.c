#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <gtk/gtk.h>

#include "system.h"
#include "fork.h"
#include "ipc.h"

void print_minios(char* str);



// static void
// print_hello (GtkWidget *widget,
//              gpointer   data)
// {
//   g_print ("Hello World\n");
// }

// static void activate (GtkApplication* app, gpointer user_data)
// {
//   GtkWidget *window;
//   GtkWidget *grid;
//   GtkWidget *button;
//   GtkWidget *label;

//   /* create a new window, and set its title */
//   window = gtk_application_window_new (app);
//   gtk_window_set_title (GTK_WINDOW (window), "miniOS");
//   gtk_container_set_border_width (GTK_CONTAINER (window), 100);

//   /* Here we construct the container that is going pack our buttons */
//   grid = gtk_grid_new ();

//   /* Pack the container in the window */
//   gtk_container_add (GTK_CONTAINER (window), grid);

//   button = gtk_button_new_with_label ("login..");
//   g_signal_connect (button, "clicked", G_CALLBACK (print_hello), NULL);

//   /* Place the first button in the grid cell (0, 0), and make it fill
//    * just 1 cell horizontally and vertically (ie no spanning)
//    */
//   gtk_grid_attach (GTK_GRID (grid), button, 0, 0, 1, 1);

//   label = gtk_label_new(NULL);  
//   gtk_label_set_markup (GTK_LABEL (label), "<small>Hello world!</small>");

//   /* Place the second button in the grid cell (1, 0), and make it fill
//    * just 1 cell horizontally and vertically (ie no spanning)
//    */
//   gtk_grid_attach (GTK_GRID (grid), label, 1, 0, 1, 1);

//   button = gtk_button_new_with_label ("Quit");
//   g_signal_connect_swapped (button, "clicked", G_CALLBACK (gtk_widget_destroy), window);

//   /* Place the Quit button in the grid cell (0, 1), and make it
//    * span 2 columns.
//    */
//   gtk_grid_attach (GTK_GRID (grid), button, 0, 1, 2, 1);

//   /* Now that we are done packing our widgets, we show them all
//    * in one go, by calling gtk_widget_show_all() on the window.
//    * This call recursively calls gtk_widget_show() on all widgets
//    * that are contained in the window, directly or indirectly.
//    */
//   gtk_widget_show_all (window);
// //   GtkWidget *window;
// //   GtkWidget *button;
// //   GtkWidget *button_box;
// //   GtkWidget *label;
// //   GtkWidget *box;

// //   window = gtk_application_window_new (app);
// //   gtk_window_set_title (GTK_WINDOW (window), "miniOS");
// //   gtk_window_set_default_size (GTK_WINDOW (window), 1000, 800);

// //   box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);

// //   button_box = gtk_button_box_new (GTK_ORIENTATION_HORIZONTAL);
// //   gtk_container_add (GTK_CONTAINER (window), button_box);

// //   button = gtk_button_new_with_label ("login..");
// //   g_signal_connect (button, "clicked", G_CALLBACK (print_hello), NULL);
// //   g_signal_connect_swapped (button, "clicked", G_CALLBACK (gtk_widget_destroy), window);
// //   gtk_container_add (GTK_CONTAINER (button_box), button);

//   label = gtk_label_new(NULL);  
//   gtk_label_set_markup (GTK_LABEL (label), "<small>Hello world!</small>");
// //   gtk_container_add(GTK_CONTAINER(window), box);
  


// //   gtk_widget_show_all (window);
// }


#define MAX_PROCESSES 5
#define TIME_QUANTUM 2

typedef struct {
    int pid; // Process ID
    int burst_time; // Burst time (time required for execution)
    int remaining_time; // Remaining time for execution
} Process;



int main(int argc, char **argv) {
    print_minios("[MiniOS SSU] Hello, World!");

    char *input;
    
  // GtkApplication *app;
  // int status;

  // app = gtk_application_new ("org.gtk.example", G_APPLICATION_FLAGS_NONE);
  // g_signal_connect (app, "activate", G_CALLBACK (activate), NULL);
  // status = g_application_run (G_APPLICATION (app), argc, argv);
  // g_object_unref (app);

  // return status;


    while(1) {
        // readline을 사용하여 입력 받기
        input = readline("커맨드를 입력하세요(종료:exit) : ");
        
	if (strcmp(input,"exit") == 0) {
            break;
        }

    else if (strcmp(input,"minisystem") == 0){
        minisystem();
    }

	else if (strcmp(input,"add") == 0){
        printf("%d\n", add());
	}

    else if (strcmp(input,"fork") == 0){
	    fork_hello();
	}

    else if (strcmp(input,"ipc") == 0){
	    ipc();
	}

    else if (strcmp(input,"pi") == 0){
        printf("pi value is: %f\n",montecarlo_pi());
  } 

    else if (strcmp(input,"rr") == 0) {
      // Define some sample processes
      Process processes[MAX_PROCESSES] = {
        {1, 4, 4},
        {2, 5, 5},
        {3, 2, 2},
        {4, 3, 3},
        {5, 6, 6}
    };
    
    // Get the number of processes
    int num_processes = sizeof(processes) / sizeof(processes[0]);
    
    roundRobinScheduler(processes, num_processes);
  }
    else system(input);

}

    // 메모리 해제
    free(input);
    print_minios("[MiniOS SSU] MiniOS Shutdown........");

    return(1);
}

void print_minios(char* str) {
        printf("%s\n",str);
}

