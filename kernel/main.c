#include <gtk/gtk.h>

// Function prototypes
static void login_button_clicked(GtkWidget *widget, gpointer data);
static void process_input(GtkWidget *widget, gpointer data);

// Global variables
GtkWidget *login_window, *welcome_window;
GtkWidget *id_entry, *pw_entry, *input_entry, *output_text;

int main(int argc, char *argv[]) {
    gtk_init(&argc, &argv);

    // Create login window
    login_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(login_window), "Login");
    gtk_window_set_default_size(GTK_WINDOW(login_window), 300, 150);
    gtk_window_set_position(GTK_WINDOW(login_window), GTK_WIN_POS_CENTER);

    GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_container_add(GTK_CONTAINER(login_window), vbox);

    GtkWidget *id_label = gtk_label_new("ID: ");
    id_entry = gtk_entry_new();
    GtkWidget *pw_label = gtk_label_new("PW: ");
    pw_entry = gtk_entry_new();
    pw_entry->visibility = FALSE;

    GtkWidget *login_button = gtk_button_new_with_label("Login");
    g_signal_connect(login_button, "clicked", G_CALLBACK(login_button_clicked), NULL);

    gtk_box_pack_start(GTK_BOX(vbox), id_label, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), id_entry, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), pw_label, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), pw_entry, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), login_button, FALSE, FALSE, 0);

    // Create welcome window
    welcome_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(welcome_window), "Welcome");
    gtk_window_set_default_size(GTK_WINDOW(welcome_window), 400, 300);
    gtk_window_set_position(GTK_WINDOW(welcome_window), GTK_WIN_POS_CENTER);

    GtkWidget *welcome_vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_container_add(GTK_CONTAINER(welcome_window), welcome_vbox);

    input_entry = gtk_entry_new();
    g_signal_connect(input_entry, "activate", G_CALLBACK(process_input), NULL);

    output_text = gtk_text_view_new();
    gtk_text_view_set_editable(GTK_TEXT_VIEW(output_text), FALSE);

    gtk_box_pack_start(GTK_BOX(welcome_vbox), input_entry, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(welcome_vbox), output_text, TRUE, TRUE, 0);

    gtk_widget_show_all(login_window);
    gtk_main();

    return 0;
}

static void login_button_clicked(GtkWidget *widget, gpointer data) {
    const gchar *id = gtk_entry_get_text(GTK_ENTRY(id_entry));
    const gchar *pw = gtk_entry_get_text(GTK_ENTRY(pw_entry));

    // Replace this with your actual login logic
    if (g_strcmp0(id, "username") == 0 && g_strcmp0(pw, "password") == 0) {
        gtk_widget_hide(login_window);
        gtk_widget_show_all(welcome_window);
    } else {
        g_print("Invalid username or password\n");
    }
}

static void process_input(GtkWidget *widget, gpointer data) {
    const gchar *input_text = gtk_entry_get_text(GTK_ENTRY(input_entry));

    GtkTextBuffer *buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(output_text));
    gtk_text_buffer_insert_at_cursor(buffer, input_text, -1);
    gtk_text_buffer_insert_at_cursor(buffer, "\n", -1);

    gtk_entry_set_text(GTK_ENTRY(input_entry), "");
}