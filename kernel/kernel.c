#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <gtk/gtk.h>

#include "system.h"
#include "fork.h"
#include "ipc.h"

// just checking
void print_minios(char* str);


// Function prototypes
static void login_button_clicked(GtkWidget *widget, gpointer data);
static void process_input(GtkWidget *widget, gpointer data);
static gboolean close_window(GtkWidget *widget, GdkEvent *event, gpointer data);

// Global variables
GtkWidget *login_window, *welcome_window;
GtkWidget *id_entry, *pw_entry, *input_entry, *output_text;

int main(int argc, char *argv[]) {
    print_minios("[MiniOS SSU] Hello, World!");

    gtk_init(&argc, &argv);

    // Create login window
    login_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(login_window), "Login");
    gtk_window_set_default_size(GTK_WINDOW(login_window), 300, 150);
    gtk_window_set_position(GTK_WINDOW(login_window), GTK_WIN_POS_CENTER);
    g_signal_connect(login_window, "delete-event", G_CALLBACK(close_window), NULL);

    GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_container_add(GTK_CONTAINER(login_window), vbox);

    GtkWidget *id_label = gtk_label_new("ID: ");
    id_entry = gtk_entry_new();
    GtkWidget *pw_label = gtk_label_new("PW: ");
    pw_entry = gtk_entry_new();
    gtk_entry_set_visibility(pw_entry, FALSE);
    // invisible?

    GtkWidget *login_button = gtk_button_new_with_label("Login");
    g_signal_connect(login_button, "clicked", G_CALLBACK(login_button_clicked), NULL);

    gtk_box_pack_start(GTK_BOX(vbox), id_label, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), id_entry, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), pw_label, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), pw_entry, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), login_button, FALSE, FALSE, 0);

    // Create welcome window
    welcome_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(welcome_window), "miniOS");
    gtk_window_set_default_size(GTK_WINDOW(welcome_window), 400, 300);
    gtk_window_set_position(GTK_WINDOW(welcome_window), GTK_WIN_POS_CENTER);
    g_signal_connect(welcome_window, "delete-event", G_CALLBACK(close_window), NULL);

    GtkWidget *welcome_vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_container_add(GTK_CONTAINER(welcome_window), welcome_vbox);

    input_entry = gtk_entry_new();
    g_signal_connect(input_entry, "activate", G_CALLBACK(process_input), NULL);

    // scroll bar
    GtkWidget *scrolled_window = gtk_scrolled_window_new(NULL, NULL);
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrolled_window), GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);


    output_text = gtk_text_view_new();
    gtk_text_view_set_editable(GTK_TEXT_VIEW(output_text), FALSE);
    gtk_container_add(GTK_CONTAINER(scrolled_window), output_text);

    gtk_box_pack_start(GTK_BOX(welcome_vbox), input_entry, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(welcome_vbox), output_text, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(welcome_vbox), scrolled_window, TRUE, TRUE, 0);

    gtk_widget_show_all(login_window);
    gtk_main();

    return 0;
}

static void login_button_clicked(GtkWidget *widget, gpointer data) {
    const gchar *id = gtk_entry_get_text(GTK_ENTRY(id_entry));
    const gchar *pw = gtk_entry_get_text(GTK_ENTRY(pw_entry));

    // maybe use hash?
    // just use strcmp for now
    if (g_strcmp0(id, "ssu") == 0 && g_strcmp0(pw, "1234") == 0) {
        gtk_widget_hide(login_window);
        gtk_widget_show_all(welcome_window);
    } else {
        g_print("Invalid username or password! Please try again.\n");
    }
}

static void process_input(GtkWidget *widget, gpointer data) {
    const gchar *input_text = gtk_entry_get_text(GTK_ENTRY(input_entry));

    gchar *result_text = gtk_entry_get_text(GTK_ENTRY(input_entry));

    GtkTextBuffer *buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(output_text));

    // Create tag for colored output
    GtkTextTag *red_tag = gtk_text_buffer_create_tag(buffer, "red_tag", "foreground", "red", NULL);

    GtkTextIter start_iter, end_iter;
    gtk_text_buffer_get_bounds(buffer, &start_iter, &end_iter);
    gtk_text_buffer_insert(buffer, &end_iter, input_text, -1);
    gtk_text_buffer_insert(buffer, &end_iter, "\n", -1);
    gtk_text_buffer_insert_with_tags_by_name(buffer, &end_iter, ">> ", -1, "red_tag", NULL);
    gtk_text_buffer_insert_with_tags_by_name(buffer, &end_iter, input_text, -1, "red_tag", NULL);
    gtk_text_buffer_insert(buffer, &end_iter, "\n", -1);

    // cmd
   	if (g_strcmp0(input_text,"exit") == 0) {
            print_minios("[MiniOS SSU] MiniOS Shutdown........");
            exit(0);
        }
    else {
    }

//     else if (strcmp(input,"minisystem") == 0){
//         minisystem();
//     }

// 	else if (strcmp(input,"add") == 0){
//         printf("%d\n", add());
// 	}

//     else if (strcmp(input,"fork") == 0){
// 	    fork_hello();
// 	}

//     else if (strcmp(input,"ipc") == 0){
// 	    ipc();
// 	}

//     else if (strcmp(input,"pi") == 0){
//         printf("pi value is: %f\n",montecarlo_pi());
//   }


    // GtkTextBuffer *buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(output_text));
    // gtk_text_buffer_insert_at_cursor(buffer, input_text, -1);
    // gtk_text_buffer_insert_at_cursor(buffer, "\n", -1);

    // gtk_text_buffer_insert_at_cursor(buffer, ">> ", -1);
    // gtk_text_buffer_insert_at_cursor(buffer, result_text, -1);
    // gtk_text_buffer_insert_at_cursor(buffer, "\n", -1);

    gtk_entry_set_text(GTK_ENTRY(input_entry), "");
}

void print_minios(char* str) {
        printf("%s\n",str);
}

static gboolean close_window(GtkWidget *widget, GdkEvent *event, gpointer data) {
    gtk_main_quit();
    return FALSE;
}