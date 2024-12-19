#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include <gtk/gtk.h>

#include "callbacks.h"
#include "interface.h"
#include "support.h"
#include "parking.h"

void
on_button2_clicked(GtkButton *button, gpointer user_data)
{
    GtkWidget *id_parking;
    GtkWidget *name_parking;
    GtkWidget *location;
    GtkWidget *capacity;
    GtkWidget *type_of_parking_private;
    GtkWidget *type_of_parking_public;
    GtkWidget *pricing_hourly;
    GtkWidget *pricing_daily;
    GtkWidget *pricing_monthly;
    GtkWidget *opening_hour;
    GtkWidget *opening_minute;
    GtkWidget *remarks;
    GtkWidget *add_parking_label;

    // Retrieve widgets by their IDs
    id_parking = lookup_widget(GTK_WIDGET(button), "entry1");
    name_parking = lookup_widget(GTK_WIDGET(button), "entry2");
    location = lookup_widget(GTK_WIDGET(button), "entry3");
    capacity = lookup_widget(GTK_WIDGET(button), "spinbutton1");
    type_of_parking_private = lookup_widget(GTK_WIDGET(button), "radiobutton2");
    type_of_parking_public = lookup_widget(GTK_WIDGET(button), "radiobutton1");
    pricing_hourly = lookup_widget(GTK_WIDGET(button), "checkbutton1");
    pricing_daily = lookup_widget(GTK_WIDGET(button), "checkbutton3");
    pricing_monthly = lookup_widget(GTK_WIDGET(button), "checkbutton2");
    opening_hour = lookup_widget(GTK_WIDGET(button), "comboboxentry1");
    opening_minute = lookup_widget(GTK_WIDGET(button), "comboboxentry2");
    remarks = lookup_widget(GTK_WIDGET(button), "entry4");
    add_parking_label = lookup_widget(GTK_WIDGET(button), "label43");

    // Reset the values of the fields
    gtk_entry_set_text(GTK_ENTRY(id_parking), "");
    gtk_entry_set_text(GTK_ENTRY(name_parking), "");
    gtk_entry_set_text(GTK_ENTRY(location), "");
    gtk_spin_button_set_value(GTK_SPIN_BUTTON(capacity), 1);
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(type_of_parking_private), TRUE);
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(type_of_parking_public), FALSE);
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(pricing_hourly), FALSE);
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(pricing_daily), FALSE);
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(pricing_monthly), FALSE);
    gtk_combo_box_set_active(GTK_COMBO_BOX(opening_hour), 0);   // Sélectionne le premier élément
    gtk_combo_box_set_active(GTK_COMBO_BOX(opening_minute), 0);
    gtk_entry_set_text(GTK_ENTRY(remarks), "");

    // Clear the status message
    gtk_label_set_text(GTK_LABEL(add_parking_label), "");
}

void
on_button1_clicked(GtkButton *button, gpointer user_data)
{
    GtkWidget *id_parking;
    GtkWidget *name_parking;
    GtkWidget *location;
    GtkWidget *capacity;
    GtkWidget *type_of_parking_private;
    GtkWidget *type_of_parking_public;
    GtkWidget *pricing_hourly;
    GtkWidget *pricing_daily;
    GtkWidget *pricing_monthly;
    GtkWidget *opening_hour;
    GtkWidget *opening_minute;
    GtkWidget *remarks;
    GtkWidget *add_parking_label;
    Parking p;

    // Retrieve widgets by their IDs
    id_parking = lookup_widget(GTK_WIDGET(button), "entry1");
    name_parking = lookup_widget(GTK_WIDGET(button), "entry2");
    location = lookup_widget(GTK_WIDGET(button), "entry3");
    capacity = lookup_widget(GTK_WIDGET(button), "spinbutton1");
    type_of_parking_private = lookup_widget(GTK_WIDGET(button), "radiobutton2");
    type_of_parking_public = lookup_widget(GTK_WIDGET(button), "radiobutton1");
    pricing_hourly = lookup_widget(GTK_WIDGET(button), "checkbutton1");
    pricing_daily = lookup_widget(GTK_WIDGET(button), "checkbutton3");
    pricing_monthly = lookup_widget(GTK_WIDGET(button), "checkbutton2");
    opening_hour = lookup_widget(GTK_WIDGET(button), "comboboxentry1");
    opening_minute = lookup_widget(GTK_WIDGET(button), "comboboxentry2");
    remarks = lookup_widget(GTK_WIDGET(button), "entry4");
    add_parking_label = lookup_widget(GTK_WIDGET(button), "label43");

    // Copy data from the fields into the Parking structure
    strcpy(p.id_parking, gtk_entry_get_text(GTK_ENTRY(id_parking)));
    strcpy(p.name_parking, gtk_entry_get_text(GTK_ENTRY(name_parking)));
    strcpy(p.location, gtk_entry_get_text(GTK_ENTRY(location)));
    p.capacity = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(capacity));

    // Determine type of parking (private or public)
    if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(type_of_parking_public))) {
        p.type_of_parking = 1; // public
    } else {
        p.type_of_parking = 0; // private
    }

    // Determine pricing options
    p.pricing[0] = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(pricing_hourly)) ? 1 : 0;
    p.pricing[1] = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(pricing_daily)) ? 1 : 0;
    p.pricing[2] = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(pricing_monthly)) ? 1 : 0;

    // Get opening time
    p.opening_time_hour = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(opening_hour));
    p.opening_time_minute = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(opening_minute));

    // Copy remarks
    strcpy(p.remarques, gtk_entry_get_text(GTK_ENTRY(remarks)));

    // Add parking data to the file
    if (addParking("parking.txt", p) == -1) {
        // Error while adding parking
        gtk_label_set_text(GTK_LABEL(add_parking_label), "Erreur : impossible d'ajouter le parking. Vérifiez les données.");
    } else {
        // Success
        gtk_label_set_text(GTK_LABEL(add_parking_label), "Parking ajouté avec succès !");
    }
}

void on_button3_clicked(GtkButton *button, gpointer user_data)
{
    GtkWidget *id_parking;
    GtkWidget *name_parking;
    GtkWidget *location;
    GtkWidget *capacity;
    GtkWidget *type_of_parking_private;
    GtkWidget *type_of_parking_public;
    GtkWidget *pricing_hourly;
    GtkWidget *pricing_daily;
    GtkWidget *pricing_monthly;
    GtkWidget *opening_hour;
    GtkWidget *opening_minute;
    GtkWidget *remarks;
    GtkWidget *search_parking_label;
    Parking p;
    char filename[] = "parking.txt";

    // Retrieve widgets by their IDs
    id_parking = lookup_widget(GTK_WIDGET(button), "entry5");
    name_parking = lookup_widget(GTK_WIDGET(button), "entry6");
    location = lookup_widget(GTK_WIDGET(button), "entry7");
    capacity = lookup_widget(GTK_WIDGET(button), "spinbutton2");
    type_of_parking_private = lookup_widget(GTK_WIDGET(button), "radiobutton7");
    type_of_parking_public = lookup_widget(GTK_WIDGET(button), "radiobutton8");
    pricing_hourly = lookup_widget(GTK_WIDGET(button), "checkbutton4");
    pricing_daily = lookup_widget(GTK_WIDGET(button), "checkbutton6");
    pricing_monthly = lookup_widget(GTK_WIDGET(button), "checkbutton5");
    opening_hour = lookup_widget(GTK_WIDGET(button), "comboboxentry9");
    opening_minute = lookup_widget(GTK_WIDGET(button), "comboboxentry4");
    remarks = lookup_widget(GTK_WIDGET(button), "entry8");
    search_parking_label = lookup_widget(GTK_WIDGET(button), "label24");

    // Retrieve the parking ID entered in the search field
    strcpy(p.id_parking, gtk_entry_get_text(GTK_ENTRY(id_parking)));

    // Search for the parking by its ID
    Parking parking_trouve = showParking(filename, p.id_parking);

    if (strlen(parking_trouve.id_parking) == 0) {
        // Parking not found
        gtk_label_set_text(GTK_LABEL(search_parking_label), "Erreur : Parking introuvable.");
        return;
    }

    // Parking found, display the details in the widgets
    gtk_entry_set_text(GTK_ENTRY(name_parking), parking_trouve.name_parking);
    gtk_entry_set_text(GTK_ENTRY(location), parking_trouve.location);
    gtk_spin_button_set_value(GTK_SPIN_BUTTON(capacity), parking_trouve.capacity);

    if (parking_trouve.type_of_parking == 1) {
        gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(type_of_parking_public), TRUE);
        gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(type_of_parking_private), FALSE);
    } else {
        gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(type_of_parking_private), TRUE);
        gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(type_of_parking_public), FALSE);
    }

    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(pricing_hourly), parking_trouve.pricing[0]);
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(pricing_daily), parking_trouve.pricing[1]);
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(pricing_monthly), parking_trouve.pricing[2]);
// Réinitialisation des heures et minutes avec les valeurs trouvées
    gtk_combo_box_set_active(GTK_COMBO_BOX(opening_hour), parking_trouve.opening_time_hour); // Sélectionne l'élément correspondant à l'heure
    gtk_combo_box_set_active(GTK_COMBO_BOX(opening_minute), parking_trouve.opening_time_minute); // Sélectionne l'élément correspondant à la minute

    gtk_entry_set_text(GTK_ENTRY(remarks), parking_trouve.remarques);

    // Display success message
    gtk_label_set_text(GTK_LABEL(search_parking_label), "Parking trouvé avec succès !");
}


void
on_button4_clicked                     (GtkButton       *button,
                                        gpointer         user_data)
{
    GtkWidget *id_parking;
    GtkWidget *name_parking;
    GtkWidget *location;
    GtkWidget *capacity;
    GtkWidget *type_of_parking_private;
    GtkWidget *type_of_parking_public;
    GtkWidget *pricing_hourly;
    GtkWidget *pricing_daily;
    GtkWidget *pricing_monthly;
    GtkWidget *opening_hour;
    GtkWidget *opening_minute;
    GtkWidget *remarks;
    GtkWidget *modify_parking_label;  // Renamed to avoid conflict with function name
    Parking p;
    char filename[] = "parking.txt";

    // Retrieve widgets by their IDs
    id_parking = lookup_widget(GTK_WIDGET(button), "entry5");
    name_parking = lookup_widget(GTK_WIDGET(button), "entry6");
    location = lookup_widget(GTK_WIDGET(button), "entry7");
    capacity = lookup_widget(GTK_WIDGET(button), "spinbutton2");
    type_of_parking_private = lookup_widget(GTK_WIDGET(button), "radiobutton7");
    type_of_parking_public = lookup_widget(GTK_WIDGET(button), "radiobutton8");
    pricing_hourly = lookup_widget(GTK_WIDGET(button), "checkbutton4");
    pricing_daily = lookup_widget(GTK_WIDGET(button), "checkbutton6");
    pricing_monthly = lookup_widget(GTK_WIDGET(button), "checkbutton5");
    opening_hour = lookup_widget(GTK_WIDGET(button), "comboboxentry9");
    opening_minute = lookup_widget(GTK_WIDGET(button), "comboboxentry4");
    remarks = lookup_widget(GTK_WIDGET(button), "entry8");
    modify_parking_label = lookup_widget(GTK_WIDGET(button), "label44");

    // Retrieve parking data from fields
    strcpy(p.id_parking, gtk_entry_get_text(GTK_ENTRY(id_parking)));
    strcpy(p.name_parking, gtk_entry_get_text(GTK_ENTRY(name_parking)));
    strcpy(p.location, gtk_entry_get_text(GTK_ENTRY(location)));
    p.capacity = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(capacity));

    // Determine type of parking (private or public)
    if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(type_of_parking_public))) {
        p.type_of_parking = 1; // public
    } else {
        p.type_of_parking = 0; // private
    }

    // Determine pricing options
    p.pricing[0] = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(pricing_hourly)) ? 1 : 0;
    p.pricing[1] = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(pricing_daily)) ? 1 : 0;
    p.pricing[2] = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(pricing_monthly)) ? 1 : 0;

    // Récupérer l'heure d'ouverture (l'élément sélectionné dans le combo box)
    p.opening_time_hour = gtk_combo_box_get_active(GTK_COMBO_BOX(opening_hour));

// Récupérer les minutes d'ouverture (l'élément sélectionné dans le combo box)
    p.opening_time_minute = gtk_combo_box_get_active(GTK_COMBO_BOX(opening_minute));


    // Copy remarks
    strcpy(p.remarques, gtk_entry_get_text(GTK_ENTRY(remarks)));

    // Search for the parking by its ID to modify it
    Parking parking_trouve = showParking(filename, p.id_parking);

    if (strlen(parking_trouve.id_parking) == 0) {
        // Parking not found
        gtk_label_set_text(GTK_LABEL(modify_parking_label), "Erreur : Parking introuvable.");
        return;
    }

    // Modify the parking data
    if (modifyParking(filename, parking_trouve.id_parking, p) == -1) {
        // Error while modifying parking
        gtk_label_set_text(GTK_LABEL(modify_parking_label), "Erreur : impossible de modifier le parking. Vérifiez les données.");
    } else {
        // Success
        gtk_label_set_text(GTK_LABEL(modify_parking_label), "Parking modifié avec succès !");
    }
}


void on_button5_clicked(GtkButton *button, gpointer user_data) {  
    

GtkWidget *treeview = lookup_widget(GTK_WIDGET(button), "treeview1");

    // Get the model associated with the treeview
    GtkTreeModel *model = gtk_tree_view_get_model(GTK_TREE_VIEW(treeview));

    if (model == NULL) {
        // If no model exists, create a new one and set it
        GtkListStore *store = create_parking_list_store();
        gtk_tree_view_set_model(GTK_TREE_VIEW(treeview), GTK_TREE_MODEL(store));
        g_object_unref(store); // Release reference as TreeView holds its own
    } else {
        // If a model already exists, clear it
        gtk_list_store_clear(GTK_LIST_STORE(model));
    }

    // Ensure columns are created only once
    if (gtk_tree_view_get_columns(GTK_TREE_VIEW(treeview)) == 0) {
        create_treeview_columns(GTK_TREE_VIEW(treeview));
    }

    // Populate the treeview with data
    populate_treeview_with_data(GTK_TREE_VIEW(treeview), "parking.txt");

}
















void
on_button7_clicked                     (GtkButton       *button,
                                        gpointer         user_data)
{
GtkWidget *treeview, *entry;
    const char *id;
    Parking *p;

    // Retrieve widgets
    treeview = lookup_widget(GTK_WIDGET(button), "treeview1");
    entry = lookup_widget(GTK_WIDGET(button), "entry9");

    // Get the ID to search for
    id = gtk_entry_get_text(GTK_ENTRY(entry));

    // Check if ID is entered
    if (strlen(id) == 0) {
        g_print("Please enter a Parking ID.\n");
        return;
    }

    // Create a new list store
    GtkListStore *store = create_parking_list_store();

    // Set the list store as the model for the tree view
    gtk_tree_view_set_model(GTK_TREE_VIEW(treeview), GTK_TREE_MODEL(store));

    // Create the tree view columns (only once)
    create_treeview_columns(GTK_TREE_VIEW(treeview));

    // Search for parking data
    p = get_parking_by_id("parking.txt", id);
    if (p != NULL) {
        insert_parking_data(store, p);
        g_print("Parking data displayed successfully.\n");
    } else {
        g_print("Parking ID not found.\n");
    }
}
void
on_button8_clicked                     (GtkButton       *button,
                                        gpointer         user_data)
{

GtkWidget *treeview, *entry;
    const char *id;
    Parking *p;

    // Retrieve widgets
    treeview = lookup_widget(GTK_WIDGET(button), "treeview2");
    entry = lookup_widget(GTK_WIDGET(button), "entry10");

    // Get the ID to search for
    id = gtk_entry_get_text(GTK_ENTRY(entry));

    // Check if ID is entered
    if (strlen(id) == 0) {
        g_print("Please enter a Parking ID.\n");
        return;
    }

    // Create a new list store
    GtkListStore *store = create_parking_list_store();

    // Set the list store as the model for the tree view
    gtk_tree_view_set_model(GTK_TREE_VIEW(treeview), GTK_TREE_MODEL(store));

    // Create the tree view columns (only once)
    create_treeview_columns(GTK_TREE_VIEW(treeview));

    // Search for parking data
    p = get_parking_by_id("parking.txt", id);
    if (p != NULL) {
        insert_parking_data(store, p);
        g_print("Parking data displayed successfully.\n");
    } else {
        g_print("Parking ID not found.\n");
    }
}

void on_button9_clicked(GtkButton *button, gpointer user_data) {
       GtkWidget *entry = lookup_widget(GTK_WIDGET(button), "entry10");
    const char *id = gtk_entry_get_text(GTK_ENTRY(entry));

    // Vérifier que l'ID n'est pas vide
    if (strlen(id) == 0) {
        GtkWidget *label_status = lookup_widget(GTK_WIDGET(button), "label34");
        gtk_label_set_text(GTK_LABEL(label_status), "Erreur : ID non fourni.");
        return;
    }

    // Supprimer le compte du fichier
    if (supprimer_parking("parking.txt", id)) {
        // Afficher un message de confirmation
        GtkWidget *label_status = lookup_widget(GTK_WIDGET(button), "label34");
        gtk_label_set_text(GTK_LABEL(label_status), "agent supprimé avec succès.");
    } else {
        // Afficher un message d'erreur
        GtkWidget *label_status = lookup_widget(GTK_WIDGET(button), "label34");
        gtk_label_set_text(GTK_LABEL(label_status), "Erreur : agent non trouvé.");
    }
}
	






void
on_radiobutton2_toggled                (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{

}
void
on_button12_clicked                    (GtkButton       *button,
                                        gpointer         user_data)
{


GtkWidget *treeview = lookup_widget(GTK_WIDGET(button), "treeview2");

    // Get the model associated with the treeview
    GtkTreeModel *model = gtk_tree_view_get_model(GTK_TREE_VIEW(treeview));

    if (model == NULL) {
        // If no model exists, create a new one and set it
        GtkListStore *store = create_parking_list_store();
        gtk_tree_view_set_model(GTK_TREE_VIEW(treeview), GTK_TREE_MODEL(store));
        g_object_unref(store); // Release reference as TreeView holds its own
    } else {
        // If a model already exists, clear it
        gtk_list_store_clear(GTK_LIST_STORE(model));
    }

    // Ensure columns are created only once
    if (gtk_tree_view_get_columns(GTK_TREE_VIEW(treeview)) == 0) {
        create_treeview_columns(GTK_TREE_VIEW(treeview));
    }

    // Populate the treeview with data
    populate_treeview_with_data(GTK_TREE_VIEW(treeview), "parking.txt");

}


void
on_radiobutton1_toggled                (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{

}


void
on_radiobutton7_toggled                (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{

}


void
on_radiobutton8_toggled                (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{

}


void
on_checkbutton1_toggled                (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{

}


void
on_checkbutton3_toggled                (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{

}


void
on_checkbutton2_toggled                (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{

}


void
on_checkbutton4_toggled                (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{

}


void
on_checkbutton6_toggled                (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{

}


void
on_checkbutton5_toggled                (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{

}






void on_button13_clicked(GtkButton *button, gpointer user_data)
{
    // Récupération des widgets
    GtkWidget *entry_id = lookup_widget(GTK_WIDGET(button), "entry11");
    GtkWidget *label_status = lookup_widget(GTK_WIDGET(button), "label45");

    if (!entry_id || !label_status) {
        g_print("Erreur : Widgets non trouvés.\n");
        return;
    }

    // Vérification de l'ID
    const char *id_text = gtk_entry_get_text(GTK_ENTRY(entry_id));
    if (!id_text || strlen(id_text) == 0) {
        gtk_label_set_text(GTK_LABEL(label_status), "Erreur : Veuillez entrer un ID.");
        g_print("Erreur : L'ID est vide.\n");
        return;
    }

    int id = atoi(id_text);
    if (id <= 0) {
        gtk_label_set_text(GTK_LABEL(label_status), "Erreur : L'ID doit être un entier positif.");
        g_print("Erreur : L'ID n'est pas valide (id=%d).\n", id);
        return;
    }

    // Recherche de l'agent
    reserv res = chercher_reserv("agent.txt", id);
    if (res.id == -1) {
        gtk_label_set_text(GTK_LABEL(label_status), "Erreur : agent introuvable.");
        g_print("Erreur : agent introuvable pour l'ID %d.\n", id);
        return;
    }

    // Mise à jour de l'interface avec les informations de l'agent
    char message[512]; // Tampon plus grand pour éviter la troncature
    int n = snprintf(message, sizeof(message), "agent trouvé : %s (%s)", res.nom, res.description);
    if (n < 0 || n >= sizeof(message)) {
        gtk_label_set_text(GTK_LABEL(label_status), "Erreur : données trop longues pour être affichées.");
        g_print("Erreur : La chaîne formatée est trop longue ou une erreur est survenue.\n");
        return;
    }

    gtk_label_set_text(GTK_LABEL(label_status), message);
    g_print("agent trouvé : %s (%s)\n", res.nom, res.description);
}


void
on_button14_clicked                    (GtkButton       *button,
                                        gpointer         user_data)
{

GtkWidget *treeview, *entry;
    const char *id;
    Parking *p;

    // Retrieve widgets
    treeview = lookup_widget(GTK_WIDGET(button), "treeview3");
    entry = lookup_widget(GTK_WIDGET(button), "entry12");

    // Get the ID to search for
    id = gtk_entry_get_text(GTK_ENTRY(entry));

    // Check if ID is entered
    if (strlen(id) == 0) {
        g_print("Please enter a Parking ID.\n");
        return;
    }

    // Create a new list store
    GtkListStore *store = create_parking_list_store();

    // Set the list store as the model for the tree view
    gtk_tree_view_set_model(GTK_TREE_VIEW(treeview), GTK_TREE_MODEL(store));

    // Create the tree view columns (only once)
    create_treeview_columns(GTK_TREE_VIEW(treeview));

    // Search for parking data
    p = get_parking_by_id("parking.txt", id);
    if (p != NULL) {
        insert_parking_data(store, p);
        g_print("Parking data displayed successfully.\n");
    } else {
        g_print("Parking ID not found.\n");
    }
}

void on_buttonaffecter_clicked(GtkButton *button, gpointer user_data) {
    GtkWidget *entry_id = lookup_widget(GTK_WIDGET(button), "entry11");   // Entry pour l'ID de réservation
    GtkWidget *entry_id1 = lookup_widget(GTK_WIDGET(button), "entry12");  // Entry pour l'ID du parking
    GtkWidget *label_status = lookup_widget(GTK_WIDGET(button), "label45");  // Label pour le statut

    if (!entry_id || !entry_id1 || !label_status) {
        g_print("Erreur : Widgets non trouvés.\n");
        return;
    }

    // Récupération de l'ID de la réservation
    const char *id_text = gtk_entry_get_text(GTK_ENTRY(entry_id));
    if (strlen(id_text) == 0) {
        gtk_label_set_text(GTK_LABEL(label_status), "Erreur : Veuillez entrer un ID de agent.");
        return;
    }

    int reservation_id = atoi(id_text);
    if (reservation_id <= 0) {
        gtk_label_set_text(GTK_LABEL(label_status), "Erreur : L'ID de agent doit être un entier positif.");
        return;
    }

    // Recherche de la réservation
    reserv reservation = chercher_reserv("agent.txt", reservation_id);
    if (reservation.id == -1) {
        gtk_label_set_text(GTK_LABEL(label_status), "Erreur : agent introuvable.");
        return;
    }

    // Récupération de l'ID du parking
    const char *id_text1 = gtk_entry_get_text(GTK_ENTRY(entry_id1));
    if (strlen(id_text1) == 0) {
        gtk_label_set_text(GTK_LABEL(label_status), "Erreur : Veuillez entrer un ID de parking.");
        return;
    }

    // Recherche du parking correspondant dans parkings.txt
    Parking parking = showParking("parking.txt", id_text1);
    if (parking.capacity == 0) {
        gtk_label_set_text(GTK_LABEL(label_status), "Erreur : Parking introuvable.");
        return;
    }

    // Vérification si cette réservation a déjà été affectée à ce parking
    FILE *f = fopen("agentaffecter.txt", "r");
    if (f != NULL) {
        char line[256];
        int res_id, park_id;
        while (fgets(line, sizeof(line), f)) {
            if (sscanf(line, "agent ID : %d Parking ID : %d", &res_id, &park_id) == 2) {
                if (res_id == reservation_id && park_id == atoi(id_text1)) {
                    gtk_label_set_text(GTK_LABEL(label_status), "Erreur : Cette agent est déjà affectée à ce parking.");
                    fclose(f);
                    return;
                }
            }
        }
        fclose(f);
    }

    // Vérification de la capacité du parking
    if (parking.capacity > 0) {
        // Mise à jour du parking en diminuant la capacité
        parking.capacity--;  // Diminuer la capacité
        if (modifyParking("parking.txt", parking.id_parking, parking)) {
            // Ajouter la réservation affectée au fichier
            f = fopen("agentaffecter.txt", "a");
            if (f != NULL) {
                fprintf(f, "agent ID : %d Parking ID : %s\n", reservation.id, parking.id_parking);
                fprintf(f, "Nom du client : %s\n", reservation.nom);
                fprintf(f, "Nom du parking : %s\n", parking.name_parking);
                fprintf(f, "Emplacement du parking : %s\n", parking.location);
                fprintf(f, "Limite de agent restante : %d\n", parking.capacity);
                fprintf(f, "Tarifs du parking : %d, %d, %d\n", parking.pricing[0], parking.pricing[1], parking.pricing[2]);
                fprintf(f, "----------------------------------------\n");
                fclose(f);

                gtk_label_set_text(GTK_LABEL(label_status), "agent affectée avec succès !");
            } else {
                gtk_label_set_text(GTK_LABEL(label_status), "Erreur : Impossible de mettre à jour le fichier.");
            }
        } else {
            gtk_label_set_text(GTK_LABEL(label_status), "Erreur : Échec de la mise à jour de la capacité du parking.");
        }
    } else {
        gtk_label_set_text(GTK_LABEL(label_status), "Erreur : Plus de places disponibles.");
    }
}



