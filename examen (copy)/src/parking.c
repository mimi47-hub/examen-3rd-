#include <stdio.h>
#include <string.h>
#include "parking.h"
#include <gtk/gtk.h>



int addParking(const char *filename, Parking p) {
    FILE *f = fopen(filename, "a");
    if (f != NULL) {
        fprintf(f, "%s %s %s %d %d %d %d %d %d %d %s\n",
                p.id_parking,
                p.name_parking,                        
                p.location,
                p.capacity,
                p.type_of_parking,
                p.pricing[0], p.pricing[1], p.pricing[2],
                p.opening_time_hour,
                p.opening_time_minute,
                p.remarques);
        fclose(f);
        return 1;
    }
    return 0;
}

int modifyParking(const char *filename, const char *id, Parking p_modify) {
    int found = 0;
    Parking p;
    FILE *f = fopen(filename, "r");
    FILE *f_temp = fopen("temp.txt", "w");

    if (f != NULL && f_temp != NULL) {
        // Lire le fichier ligne par ligne
        while (fscanf(f, "%s %s %s %d %d %d %d %d %d %d %s",
                p.id_parking,
                p.name_parking,                        
                p.location,
                &p.capacity,
                &p.type_of_parking,
                &p.pricing[0], &p.pricing[1], &p.pricing[2],
                &p.opening_time_hour,
                &p.opening_time_minute,
                p.remarques) != EOF) {

            // Si l'ID du parking correspond, le modifier
            if (strcmp(p.id_parking, id) == 0) {
                fprintf(f_temp, "%s %s %s %d %d %d %d %d %d %d %s\n",
                        p_modify.id_parking,
                        p_modify.name_parking,
                        p_modify.location,
                        p_modify.capacity,
                        p_modify.type_of_parking,                        
                        p_modify.pricing[0], p_modify.pricing[1], p_modify.pricing[2],
                        p_modify.opening_time_hour,
                        p_modify.opening_time_minute,
                        p_modify.remarques);
                found = 1;
            } else {
                // Si l'ID ne correspond pas, écrire la ligne inchangée
                fprintf(f_temp, "%s %s %s %d %d %d %d %d %d %d %s\n",
                        p.id_parking,
                        p.name_parking,
                        p.location,
                        p.capacity,
                        p.type_of_parking,                        
                        p.pricing[0], p.pricing[1], p.pricing[2],
                        p.opening_time_hour,
                        p.opening_time_minute,
                        p.remarques);
            }
        }

        fclose(f);
        fclose(f_temp);

        // Remplacer l'ancien fichier par le fichier temporaire
        if (found) {
            remove(filename);
            rename("temp.txt", filename);
        } else {
            // Supprimer le fichier temporaire si aucune modification n'a été effectuée
            remove("temp.txt");
        }
    }

    return found;  // Retourne 1 si trouvé et modifié, sinon 0
}
// Supprimer un parking
int removeParking(const char *filename, const char *id){
    int found = 0;
    Parking p;
    FILE *f = fopen(filename, "r");
    FILE *f_temp = fopen("temp.txt", "w");
    if (f != NULL && f_temp != NULL) {
        while (fscanf(f, "%s %s %s %d %d %d %d %d %d %d %s",
                p.id_parking,
                p.name_parking,                        
                p.location,
                &p.capacity,
                &p.type_of_parking,                
                &p.pricing[0], &p.pricing[1], &p.pricing[2],
                &p.opening_time_hour,
                &p.opening_time_minute,
                p.remarques) != EOF) {

            if (strcmp(p.id_parking, id) != 0) {
                fprintf(f_temp, "%s %s %s %d %d %d %d %d %d %d %s\n",
                        p.id_parking,
                        p.name_parking,
                        p.location,
                        p.capacity,
                        p.type_of_parking,                        
                        p.pricing[0], p.pricing[1], p.pricing[2],
                        p.opening_time_hour,
                        p.opening_time_minute,
                        p.remarques);
            } else {
                printf("Deleting parking ID: %s\n", p.id_parking); 
                found = 1;
            }
        }

        fclose(f);
        fclose(f_temp);
        remove(filename);
        rename("temp.txt", filename);
    }
    return found;
}

Parking showParking(const char *filename, const char *id) {
    Parking p;
    int found = 0;
    FILE *f = fopen(filename, "r");

    if (f != NULL) {
        while (!found && fscanf(f, "%s %s %s %d %d %d %d %d %d %d %s\n",
                p.id_parking,
                p.name_parking,
                p.location,
                &p.capacity,
                &p.type_of_parking,               
                &p.pricing[0], &p.pricing[1], &p.pricing[2],
                &p.opening_time_hour,
                &p.opening_time_minute,
                p.remarques) != EOF) {
            
              if (strcmp(p.id_parking, id) == 0) {
                found = 1;
            }
        }
        fclose(f);
    }
    if (!found) {
        strcpy(p.id_parking, "");  // Empty ID signifies not found
    }

  return p;
} 
// Afficher tous les parkings
void AfficherParkings(char *filename) {
    Parking p;
    FILE *f = fopen(filename, "r");
    if (f != NULL) {
        printf("Liste des parkings :\n");
        while (fscanf(f, "%s %s %s %d %d %d %d %d %d %d %s\n", 
                      p.id_parking, p.name_parking, p.location,
                      &p.capacity, &p.type_of_parking,               
                      &p.pricing[0], &p.pricing[1], &p.pricing[2],
                      &p.opening_time_hour, &p.opening_time_minute, p.remarques) != EOF) {
            printf("ID: %s, Name: %s, Location: %s, Capacity: %d, Type: %d, Pricing: %d-%d-%d, Opening Time: %d:%d, Remarks: %s\n",
                   p.id_parking, p.name_parking, p.location,
                   p.capacity, p.type_of_parking,
                   p.pricing[0], p.pricing[1], p.pricing[2],
                   p.opening_time_hour, p.opening_time_minute, p.remarques);
        }
        fclose(f);
    } else {
        printf("Erreur lors de l'ouverture du fichier des parkings.\n");
    }
}

int RechercherAgent(char *filename, char *idRecherche) {
    Agent a;
    FILE *f = fopen(filename, "r");
    if (f != NULL) {
        while (fscanf(f, "%s %s %s %s %d %s %d %d %d %c %d %d %d\n",
                      a.id, a.nom, a.prenom, a.adresse, &a.governorate, a.email,
                      &a.jour, &a.mois, &a.annee, &a.sexe,
                      &a.pricing[0], &a.pricing[1], &a.phone) != EOF) {
            if (strcmp(a.id, idRecherche) == 0) {
                fclose(f);
                return 1; // Agent trouvé
            }
        }
        fclose(f);
    }
    return 0; // Agent non trouvé ou fichier inaccessible
}

void AfficherAgents(char *filename) {
    Agent a;
    FILE *f = fopen(filename, "r");
    if (f != NULL) {
        printf("Liste des agents :\n");
        printf("ID\tNom\t\tPrenom\t\tAdresse\t\tGouvernorat\tEmail\t\tNaissance\tSexe\tTarifs\t\tTelephone\n");
        printf("------------------------------------------------------------------------------------------------------------\n");
        while (fscanf(f, "%s %s %s %s %d %s %d %d %d %c %d %d %d\n",
                      a.id, a.nom, a.prenom, a.adresse, &a.governorate, a.email,
                      &a.jour, &a.mois, &a.annee, &a.sexe,
                      &a.pricing[0], &a.pricing[1], &a.phone) != EOF) {
            printf("%s\t%s\t\t%s\t\t%s\t%d\t\t%s\t%d/%d/%d\t%c\t%d-%d\t\t%d\n",
                   a.id, a.nom, a.prenom, a.adresse, a.governorate, a.email,
                   a.jour, a.mois, a.annee, a.sexe,
                   a.pricing[0], a.pricing[1], a.phone);
        }
        fclose(f);
    } else {
        printf("Erreur lors de l'ouverture du fichier des agents.\n");
    }
}


// Affecter un agent à un parking
int AffecterAgent(char *filename, int id_parking, Agent agent) {
    FILE *f = fopen(filename, "r");
    char buffer[256];
    int agentAffecte = 0;
    int idAgent, idParking;

    // Vérifier si l'agent est déjà affecté
    if (f != NULL) {
        while (fgets(buffer, sizeof(buffer), f)) {
            if (strstr(buffer, "Agent") && strstr(buffer, "affecté au Parking")) {
                sscanf(buffer, "Agent %d affecté au Parking %d", &idAgent, &idParking);
                if (idAgent == atoi(agent.id)) {
                    agentAffecte = 1;
                    break;
                }
            }
        }
        fclose(f);
    }

    if (agentAffecte) {
        printf("Erreur : Cet agent est déjà affecté à un autre parking.\n");
        return 0;
    }

    // Affecter l'agent au parking
    f = fopen(filename, "a");
    if (f != NULL) {
        fprintf(f, "Agent %s affecté au Parking %d\n", agent.id, id_parking);
        fclose(f);
        return 1;
    }
    return 0;
}
/*
Parking load_Parking(const char *filename, const char *id) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        Parking p = {0};
        strcpy(p.id_parking, "-1");
        return p;
    }

    Parking p;
    int found = 0;
    while (fscanf(file, 
            "%49[^,],%49[^,],%99[^,],%d,%d,%d,%d,%d,%d,%d,%199[^\n]",
            p.id_parking, 
            p.name_parking, 
            p.location, 
            &p.capacity, 
            &p.type_of_parking, 
            &p.pricing[0], 
            &p.pricing[1], 
            &p.pricing[2], 
            &p.opening_time_hour, 
            &p.opening_time_minute, 
            p.remarques) != EOF) {
        // Validate each string for UTF-8 encoding
        if (!g_utf8_validate(p.id_parking, -1, NULL)) strcpy(p.id_parking, "Invalid UTF-8");
        if (!g_utf8_validate(p.name_parking, -1, NULL)) strcpy(p.name_parking, "Invalid UTF-8");
        if (!g_utf8_validate(p.location, -1, NULL)) strcpy(p.location, "Invalid UTF-8");
        if (!g_utf8_validate(p.remarques, -1, NULL)) strcpy(p.remarques, "Invalid UTF-8");

        // Check if the current parking ID matches the requested ID
        if (strcmp(p.id_parking, id) == 0) {
            found = 1;
            break;
        }
    }

    fclose(file);
    if (!found) {
        strcpy(p.id_parking, "-1");
    }
    return p;
}


Parking* get_parking_by_id(const char *filename, const char *id) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        return NULL;
    }

    static Parking p;  // Use static to retain the value after closing the file
    char line[1024];

    while (fgets(line, sizeof(line), file)) {
        // Correct sscanf usage for reading the line
        if (sscanf(line, 
            "%49[^,],%49[^,],%99[^,],%d,%d,%d,%d,%d,%d,%d,%199[^\n]",
            p.id_parking, 
            p.name_parking, 
            p.location, 
            &p.capacity, 
            &p.type_of_parking, 
            &p.pricing[0], 
            &p.pricing[1], 
            &p.pricing[2], 
            &p.opening_time_hour, 
            &p.opening_time_minute, 
            p.remarques) == 11) {  // Ensure that 11 items are read correctly
            // Check if the parking ID matches
            if (strcmp(p.id_parking, id) == 0) {
                fclose(file);
                return &p;  // Return pointer to the found parking
            }
        }
    }

    fclose(file);
    return NULL;  // Return NULL if parking ID is not found
}




GtkListStore *create_parking_list_store() {
    return gtk_list_store_new(
    9,                              // Nombre total de colonnes
    G_TYPE_STRING,                  // id_parking (chaîne de caractères)
    G_TYPE_STRING,                  // name_parking (chaîne de caractères)
    G_TYPE_STRING,                  // location (chaîne de caractères)
    G_TYPE_INT,                     // capacity (entier)
    G_TYPE_INT,                     // type_of_parking (entier)
    G_TYPE_INT,                     // pricing[0] (entier)
    G_TYPE_INT,                     // pricing[1] (entier)
    G_TYPE_INT,                     // pricing[2] (entier)
    G_TYPE_STRING                   // remarques (chaîne de caractères)
);
}
void create_treeview_columns(GtkTreeView *treeview) {
    GtkCellRenderer *renderer;
    GtkTreeViewColumn *column;

    // Column 1: Parking ID
    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes("Parking ID", renderer, "text", 0, NULL);
    gtk_tree_view_append_column(treeview, column);

    // Column 2: Parking Name
    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes("Name", renderer, "text", 1, NULL);
    gtk_tree_view_append_column(treeview, column);

    // Column 3: Location
    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes("Location", renderer, "text", 2, NULL);
    gtk_tree_view_append_column(treeview, column);

    // Column 4: Capacity
    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes("Capacity", renderer, "text", 3, NULL);
    gtk_tree_view_append_column(treeview, column);

    // Column 5: Type of Parking
    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes("Type of Parking", renderer, "text", 4, NULL);
    gtk_tree_view_append_column(treeview, column);

    // Column 6: Pricing - Price 1 (for example, per hour)
    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes("Price 1", renderer, "text", 5, NULL);
    gtk_tree_view_append_column(treeview, column);

    // Column 7: Pricing - Price 2 (for example, per day)
    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes("Price 2", renderer, "text", 6, NULL);
    gtk_tree_view_append_column(treeview, column);

    // Column 8: Pricing - Price 3 (for example, per annual subscription)
    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes("Price 3", renderer, "text", 7, NULL);
    gtk_tree_view_append_column(treeview, column);

    // Column 9: Opening Time Hour
    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes("Opening Time Hour", renderer, "text", 8, NULL);
    gtk_tree_view_append_column(treeview, column);

    // Column 10: Opening Time Minute
    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes("Opening Time Minute", renderer, "text", 9, NULL);
    gtk_tree_view_append_column(treeview, column);

    // Column 11: Remarks
    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes("Remarks", renderer, "text", 10, NULL);
    gtk_tree_view_append_column(treeview, column);
}
void setup_treeview(GtkWidget *treeview) {
    // Create the list store
    GtkListStore *store = create_parking_list_store();

    // Set the model for the treeview
    gtk_tree_view_set_model(GTK_TREE_VIEW(treeview), GTK_TREE_MODEL(store));

    // Create the columns
    create_treeview_columns(GTK_TREE_VIEW(treeview));
}
void insert_parking_data(GtkListStore *store, Parking *p) {
    GtkTreeIter iter;
    
    // Append a new row to the list store
    gtk_list_store_append(store, &iter);

    // Set data for each column in the new row
    gtk_list_store_set(store, &iter,
                       0, p->id_parking,                    // Parking ID
                       1, p->name_parking,                  // Parking Name
                       2, p->location,                      // Location
                       3, p->capacity,                      // Capacity
                       4, p->type_of_parking,               // Type of Parking
                       5, p->pricing[0],                    // Price 1 (e.g., per hour)
                       6, p->pricing[1],                    // Price 2 (e.g., per day)
                       7, p->pricing[2],                    // Price 3 (e.g., annual subscription)
                       8, p->opening_time_hour,             // Opening Time Hour
                       9, p->opening_time_minute,           // Opening Time Minute
                       10, p->remarques,                    // Remarks
                       -1);                                 // End of arguments
}
*/
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Function to create a GtkListStore for Parking
/*
GtkListStore *create_parking_list_store() {
    // Define the data types for the columns
    return gtk_list_store_new(9, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING,
                                 G_TYPE_INT, G_TYPE_STRING, G_TYPE_STRING,
                                 G_TYPE_INT, G_TYPE_INT, G_TYPE_STRING);
}

// Function to create columns for the TreeView
void create_treeview_columns(GtkTreeView *treeview) {
    GtkCellRenderer *renderer;
    GtkTreeViewColumn *column;

    // Column 1: ID
    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes("ID Parking", renderer, "text", 0, NULL);
    gtk_tree_view_append_column(treeview, column);

    // Column 2: Name
    column = gtk_tree_view_column_new_with_attributes("Name", renderer, "text", 1, NULL);
    gtk_tree_view_append_column(treeview, column);

    // Column 3: Location
    column = gtk_tree_view_column_new_with_attributes("Location", renderer, "text", 2, NULL);
    gtk_tree_view_append_column(treeview, column);

    // Column 4: Capacity
    column = gtk_tree_view_column_new_with_attributes("Capacity", renderer, "text", 3, NULL);
    gtk_tree_view_append_column(treeview, column);

    // Column 5: Type of Parking
    column = gtk_tree_view_column_new_with_attributes("Type", renderer, "text", 4, NULL);
    gtk_tree_view_append_column(treeview, column);

    // Column 6: Pricing
    column = gtk_tree_view_column_new_with_attributes("Pricing", renderer, "text", 5, NULL);
    gtk_tree_view_append_column(treeview, column);

    // Column 7: Opening Hour
    column = gtk_tree_view_column_new_with_attributes("Opening Hour", renderer, "text", 6, NULL);
    gtk_tree_view_append_column(treeview, column);

    // Column 8: Opening Minute
    column = gtk_tree_view_column_new_with_attributes("Opening Min", renderer, "text", 7, NULL);
    gtk_tree_view_append_column(treeview, column);

    // Column 9: Remarks
    column = gtk_tree_view_column_new_with_attributes("Remarks", renderer, "text", 8, NULL);
    gtk_tree_view_append_column(treeview, column);
}

// Function to search for parking information by ID
Parking *get_parking_by_id(const char *filename, const char *id) {
    static Parking p;  // Use static to retain scope after function returns
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Error opening file");
        return NULL;
    }

    printf("Looking for Parking ID: %s\n", id);  // Debugging statement

    // Read each line and match the ID
    while (fscanf(file, "%49s %49s %99s %d %d %d %d %d %d %d %[^\n]",
                  p.id_parking,
                  p.name_parking,
                  p.location,
                  &p.capacity,
                  &p.type_of_parking,
                  &p.pricing[0],
                  &p.pricing[1],
                  &p.pricing[2],
                  &p.opening_time_hour,
                  &p.opening_time_minute,
                  p.remarques) == 11) {
        
        printf("Read ID: %s\n", p.id_parking);  // Debugging statement
        if (strcmp(p.id_parking, id) == 0) {
            printf("Match found!\n");  // Debugging statement
            fclose(file);
            return &p;  // Return parking structure if ID matches
        }
    }

    printf("No match found for ID: %s\n", id);
    fclose(file);
    return NULL;  // Not found
}


// Function to insert parking data into the list store
void insert_parking_data(GtkListStore *store, Parking *p) {
    GtkTreeIter iter;
    char pricing[100];

    // Convert pricing to a readable string
    snprintf(pricing, sizeof(pricing), "Hourly: %d, Daily: %d, Monthly: %d",
             p->pricing[0], p->pricing[1], p->pricing[2]);

    // Insert data into the list store
    gtk_list_store_append(store, &iter);
    gtk_list_store_set(store, &iter,
                       0, p->id_parking,
                       1, p->name_parking,
                       2, p->location,
                       3, p->capacity,
                       4, p->type_of_parking == 0 ? "Public" : "Private",
                       5, pricing,
                       6, p->opening_time_hour,
                       7, p->opening_time_minute,
                       8, p->remarques,
                       -1);
}
*/// Function to create a GtkListStore with column types
GtkListStore *create_parking_list_store() {
    return gtk_list_store_new(9,
                              G_TYPE_STRING,  // ID
                              G_TYPE_STRING,  // Name
                              G_TYPE_STRING,  // Location
                              G_TYPE_INT,     // Capacity
                              G_TYPE_STRING,  // Type of Parking
                              G_TYPE_STRING,  // Pricing
                              G_TYPE_INT,     // Opening Hour
                              G_TYPE_INT,     // Opening Minute
                              G_TYPE_STRING); // Remarks
}

// Function to create columns for the TreeView
void create_treeview_columns(GtkTreeView *treeview) {
    GtkCellRenderer *renderer = gtk_cell_renderer_text_new();
    GtkTreeViewColumn *column;

    const char *column_titles[] = {"ID Parking", "Name", "Location", "Capacity",
                                   "Type", "Pricing", "Opening Hour", "Opening Min", "Remarks"};

    for (int i = 0; i < 9; i++) {
        column = gtk_tree_view_column_new_with_attributes(column_titles[i], renderer, "text", i, NULL);
        gtk_tree_view_append_column(treeview, column);
    }
}

// Function to search for parking information by ID
Parking *get_parking_by_id(const char *filename, const char *id) {
    static Parking p; // Static to retain scope
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Error opening file");
        return NULL;
    }

    printf("Looking for Parking ID: %s\n", id); // Debug

    char line[512]; // Buffer to read lines
    while (fgets(line, sizeof(line), file)) {
        // Clear structure to avoid garbage values
        memset(&p, 0, sizeof(Parking));

        // Parse the line
        if (sscanf(line, "%49s %49s %99s %d %d %d %d %d %d %d %[^\n]",
                   p.id_parking, p.name_parking, p.location, &p.capacity,
                   &p.type_of_parking, &p.pricing[0], &p.pricing[1], &p.pricing[2],
                   &p.opening_time_hour, &p.opening_time_minute, p.remarques) == 11) {

            printf("Read ID: %s\n", p.id_parking); // Debug
            if (strcmp(p.id_parking, id) == 0) {
                printf("Match found!\n");
                fclose(file);
                return &p;
            }
        } else {
            printf("Skipping invalid line: %s\n", line); // Debug invalid line
        }
    }

    printf("No match found for ID: %s\n", id);
    fclose(file);
    return NULL;
}

// Function to insert parking data into the list store
void insert_parking_data(GtkListStore *store, Parking *p) {
    GtkTreeIter iter;
    char pricing[100];

    // Convert pricing to a readable string
    snprintf(pricing, sizeof(pricing), "Hourly: %d, Daily: %d, Monthly: %d",
             p->pricing[0], p->pricing[1], p->pricing[2]);

    // Insert data into the list store
    gtk_list_store_append(store, &iter);
    gtk_list_store_set(store, &iter,
                       0, p->id_parking,
                       1, p->name_parking,
                       2, p->location,
                       3, p->capacity,
                       4, (p->type_of_parking == 0) ? "Public" : "Private",
                       5, pricing,
                       6, p->opening_time_hour,
                       7, p->opening_time_minute,
                       8, p->remarques,
                       -1);
}
void populate_treeview_with_data(GtkTreeView *treeview, const char *filename) {
    GtkListStore *store = create_parking_list_store(); // Function to create list store
    FILE *file = fopen(filename, "r");

    if (file == NULL) {
        g_print("Error: Could not open the file\n");
        return;
    }

    Parking p;
    GtkTreeIter iter;

    // Read file line by line and parse into the Parking structure
    while (fscanf(file, "%49s %49s %99s %d %d %d %d %d %d %d %[^\n]",
                  p.id_parking,
                  p.name_parking,
                  p.location,
                  &p.capacity,
                  &p.type_of_parking,
                  &p.pricing[0], // Hourly pricing
                  &p.pricing[1], // Daily pricing
                  &p.pricing[2], // Monthly pricing
                  &p.opening_time_hour,
                  &p.opening_time_minute,
                  p.remarques) == 11) {

        // Add data to the ListStore
        gtk_list_store_append(store, &iter);
        gtk_list_store_set(store, &iter,
                           0, p.id_parking,
                           1, p.name_parking,
                           2, p.location,
                           3, p.capacity,
                           4, (p.type_of_parking == 0) ? "Public" : "Private", // Type
                           5, g_strdup_printf("Hourly: %d, Daily: %d, Monthly: %d", 
                                              p.pricing[0], p.pricing[1], p.pricing[2]), // Pricing
                           6, p.opening_time_hour,  // Opening hour
                           7, p.opening_time_minute, // Opening minute
                           8, p.remarques, // Remarks
                           -1);
    }

    fclose(file);

    // Set the list store as the model for the tree view
    gtk_tree_view_set_model(treeview, GTK_TREE_MODEL(store));
    g_object_unref(store); // Decrease reference count
}
int supprimer_parking(const char *filename, const char *id) {
    FILE *f = fopen(filename, "r");
    if (f == NULL) {
        printf("Erreur : Impossible d'ouvrir le fichier %s.\n", filename);
        return 0;
    }

    FILE *temp = fopen("temp.txt", "w");
    if (temp == NULL) {
        fclose(f);
        printf("Erreur : Impossible de créer le fichier temporaire.\n");
        return 0;
    }

    Parking p;
    char line[512];
    int found = 0;

    // Lire le fichier ligne par ligne
    while (fgets(line, sizeof(line), f)) {
        // Utilisation de sscanf pour lire la ligne et remplir la structure 'Parking'
        if (sscanf(line, "%49s %49s %99s %d %d %d %d %d %d %d %[^\n]",
                   p.id_parking, p.name_parking, p.location, &p.capacity,
                   &p.type_of_parking, &p.pricing[0], &p.pricing[1], &p.pricing[2],
                   &p.opening_time_hour, &p.opening_time_minute, p.remarques) == 11) {

            // Vérifier si l'ID correspond
            if (strcmp(p.id_parking, id) == 0) {
                found = 1; // Marquer comme trouvé
                continue;  // Ne pas écrire cette ligne dans le fichier temporaire
            }
        }

        // Écrire les lignes non supprimées dans le fichier temporaire
        fprintf(temp, "%s", line);
    }

    fclose(f);
    fclose(temp);

    if (found) {
        remove(filename);  // Supprimer l'ancien fichier
        rename("temp.txt", filename);  // Renommer le fichier temporaire
        return 1; // Succès
    } else {
        remove("temp.txt");
        printf("Erreur : Parking avec l'ID '%s' introuvable.\n", id);
        return 0; // Échec
    }
}

reserv chercher_reserv(const char *filename, int id) {
    reserv r;
    r.id = -1;  // Valeur par défaut si le service n'est pas trouvé

    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Erreur : Impossible d'ouvrir le fichier");
        return r;
    }

    char line[512];
    while (fgets(line, sizeof(line), file)) {
        reserv temp; // Utilisation cohérente de la même structure
        if (sscanf(line, "%d|%49[^|]|%49[^|]|%199[^|]|%14[^|]",
                   &temp.id, temp.nom, temp.categorie, temp.description, temp.telephone) == 5) {
            if (temp.id == id) {
                r = temp;
                break;
            }
        }
    }

    fclose(file);
    return r;
}
