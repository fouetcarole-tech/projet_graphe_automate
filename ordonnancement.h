#ifndef ORDONNANCEMENT_H
#define ORDONNANCEMENT_H

#define PAS_D_ARC (-1000000)
#define TAILLE_CHEMIN 256

typedef struct {
    int nb_taches;
    int *duree;
    int *nb_preds;
    int **preds;
} TableauContraintes;

typedef struct {
    int nb_sommets;
    int nb_arcs;
    int **matrice;
} Graphe;

/* ---------- Étape 1 : lecture et stockage du tableau de contraintes ---------- */
TableauContraintes *lire_tableau_contraintes(const char *chemin_fichier);
void afficher_tableau_contraintes(const TableauContraintes *tc);
void liberer_tableau_contraintes(TableauContraintes *tc);

/* ---------- Étape 2 : construction et affichage du graphe ---------- */
Graphe *construire_graphe(const TableauContraintes *tc);
void afficher_triplets(const Graphe *g);
void afficher_matrice(const Graphe *g);
void liberer_graphe(Graphe *g);

/* ---------- Étape 3 : vérification des propriétés ---------- */
int trouver_points_entree(const Graphe *g, int *liste);
int trouver_points_sortie(const Graphe *g, int *liste);
int detecter_circuit(const Graphe *g);
int a_arc_negatif(const Graphe *g);
int est_graphe_ordonnancement(const Graphe *g);

/* ---------- Étape 4 : rangs (tri topologique) ---------- */
int calculer_rangs(const Graphe *g, int *rangs);
void afficher_rangs(const Graphe *g, const int *rangs);

/* ---------- Étape 5 : calendriers et marges ---------- */
void calculer_calendrier_plus_tot(const Graphe *g, const int *rangs, int *date_tot);
int calculer_duree_projet(const Graphe *g, const int *date_tot);
void calculer_calendrier_plus_tard(const Graphe *g, const int *rangs, const int *date_tot, int *date_tard);
void calculer_marges(const Graphe *g, const int *date_tot, const int *date_tard, int *marges);
void afficher_calendriers_et_marges(const Graphe *g, const int *rangs, const int *date_tot, const int *date_tard, const int *marges);

/* ---------- Étape 7 : chemins critiques ---------- */
int est_sommet_critique(int sommet, const int *marges);
int est_arc_critique(const Graphe *g, int i, int j, const int *date_tot, const int *date_tard);
void chercher_chemins_critiques(const Graphe *g, const int *date_tot, const int *date_tard, int sommet, int *chemin, int profondeur, int *nb_chemins);
void afficher_chemins_critiques(const Graphe *g, const int *date_tot, const int *date_tard);

/* ---------- Programme principal et boucle de test ---------- */
void traiter_tableau(const char *chemin_fichier);
void demander_nom_fichier(char *chemin_fichier, int taille);
int demander_continuer(void);

#endif
