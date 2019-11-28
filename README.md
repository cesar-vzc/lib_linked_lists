# Librairie 
# - Liste simplement chainées

## Description

*Création d'une librairie sur les listes simplement chainées contenant plusieurs fonctions afin de faciliter l'utilisation de celles-ci.*

*La structure est la suivante :*

	struct list {
		struct list *next;
		int data;
	};
	
*Une liste chainée peut être utilisée afin de stocker dynamiquement des données et d'en rajouter/supprimer où on veut dans la liste.*

### Fonctions

#### Init

	struct list *list_init()

Cette fonction permet d'initialiser la liste; elle alloue la place mémoire nécessaire pour la structure puis initialise le chunk suivant à NULL.

La fonction ne prend aucun paramètre et return le premier élement de la liste.

#### Push

	int list_push(struct list **list, const char *value)
	
Cette fonction permet d'insérer un élément dans la liste; elle convertie la valeur en un entier puis insert le nouveau chunk contenant la donnée en le faisant pointer sur le chunk suivant.

La fonction prend deux paramètres :

- la liste

- la donnée à ajouter

Si le chunk a bien été ajouté, la fonction return 0.

En cas d'erreur, celle-ci return -1.

#### Del By Data

	int list_del_by_data(struct list **list, const char *data)

Cette fonction supprime un chunk grâce à une donnée envoyée; elle convertie la valeur en un entier puis parcourt la liste jusqu'à trouver le chunk contenant la donnée, mémorise sont emplacement afin de le free et enfin le supprime.

La fonction prend deux paramètres :

- la liste

- la donnée à comparer

Si le chunk a bien été supprimé, la fonction return 0.

En cas d'erreur, celle-ci return -1.

#### Free

	void list_free(struct list *list)
	
Cette fonction libère toute la mémoire utilisée pour la liste.

La fonction prend uniquement la liste en paramètre et ne return rien.

#### Len

	int list_len(struct list *list)
	
Cette fonction compte le nombre de chunks dans la liste.

La fonction prend uniquement la liste en paramètre et return la taille de la liste.

#### Print

	void list_print(struct list *list)
	
Cette fonction affiche les données (chunk par chunk) contenues dans la liste jusqu'à la fin de celle-ci (NULL).

La fonction prend uniquement la liste en paramètre et ne return rien.

### Exemple d'utilisation

	cesar@debian:~/Stage/liste$ ./liste
	La liste contient 8 chunk(s).
	Erreur: 'a' caractère(s) invalide(s).
	Erreur: 'aaa' caractère(s) invalide(s).
	Erreur: impossible de push NULL.
	Erreur: impossible de push NULL.
	1 -> 3 -> 55 -> NULL
	La liste contient 3 chunk(s).
	Liste free.
	La liste contient 0 chunk(s).

**main de l'exemple**

	int main(void) {
		int i;
		int size;
		const char *tab_add[] =	{"0","0","1","11","3","5","55","8"};
		const char *tab_del[] = {"0","11","5","8"};
		const char *tab_bad[] = {"12a", "aaa", "", NULL};
		struct list *list = NULL;

	  	size = sizeof(tab_add)/sizeof(char*);
	  	for (i = 0; i < size; i++)
    		list_push(&list, tab_add[i]);

	  	printf("La liste contient %d chunk(s).\n", list_len(list));

	  	size = sizeof(tab_bad)/sizeof(char*);
	  	for (i = 0; i < size; i++)
	  		list_push(&list, tab_bad[i]);

	  	size = sizeof(tab_bad)/sizeof(char*);
	  	for (i = 0; i < size; i++)
	  		list_del_by_data(&list, tab_bad[1]);

	  	size = sizeof(tab_del)/sizeof(char*);
	  	for (i = 0; i < size; i++)
	  		list_del_by_data(&list, tab_del[i]);

	  	list_print(list);
	  	printf("La liste contient %d chunk(s).\n", list_len(list));
	  	list_free(list);
	  	list = NULL;
	  	printf("La liste contient %d chunk(s).\n", list_len(list));
	  	return 0;
	}

### Conclusion

Personnellement, j'ai trouvé la conception de cette librairie intéressante étant donné certaines lacunes de ma part dans cette notion. Faire ces fonctions m'a grandement aidé afin de bien comprendre les listes chainées et leur utilisation. J'ai rencontré plusieurs problèmes sur l'utilisation des pointeurs que je ne maîtrise pas encore totalement mais que je visualise mieux.

Auteur : *César VENZAC*

Tuteurs : *Nicolas VILMAIN et Vincent KHERBACHE*

