#include <sys/select.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/types.h>     
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>

int affiche_adresse_socket (int sock);
int   cree_socket_stream(const char * nom_hote,const char * nom_service, 
                             const char * nom_proto);
int quitter_le_serveur();
void traite_connexion(int sock_connectee);
void envoi(int sock_connecte);

int main()
{



struct sockaddr adresse;
socklen_t longueur;
int sock_connecte;
int sock_serv;


int v_affich; // Pour acceuillir la valeur de retour de la fonction d'affichage        des             propriétés du serveur



fprintf(stdout, " Demarrage du serveur ");
if ((sock_serv= cree_socket_stream(NULL, NULL, "tcp")) < 0)
		exit(EXIT_FAILURE);



fprintf(stdout, "\n Adresse >> ");
if ((v_affich=affiche_adresse_socket (sock_serv)) != 0) 
      exit(EXIT_FAILURE);  
if (listen(sock_serv,10) == -1)
    {
        printf("Failed to listen\n");
        return -1;
    }
    
    

	while (! quitter_le_serveur()) 
	{
	longueur = sizeof(struct sockaddr_in);
	sock_connecte = accept(sock_serv, & adresse, & longueur);
	
	if (sock_connecte< 0) 
	{
	perror(" Erreur durant accept ");
	return -1;
	}
	
	
	switch (fork()) 
	     {
		case 0 :   // fils 
		close(sock_serv);
		//traite_connexion(sock_connecte);
		envoi(sock_connecte);
		exit(EXIT_SUCCESS);
		
		case (0-1):
		perror(" Erreur de création du processus adjoint : fork");
		return -1;
		
		default :  // père
		close(sock_connecte);
	     } 
	 
	 

         }

      return 0;
}


void envoi(int sock_connecte)
{
          FILE* fichier_envoy=NULL;
          int caractere_actuel;
	  fprintf(stdout, "tentative de connexion\n");
	  fprintf(stdout, "Identification du fichier demandé par le client\n");
	
	
	  // Vérifier l'accès effectif au fichier
		
		char buffer[14];
		read(sock_connecte,buffer,sizeof(char)*14);
		char* nom__fichier=buffer;
		if ((fichier_envoy=fopen( ( const char *) nom__fichier,"r")) == NULL )
		{  
		fprintf(stdout," CONTENU DE FICHIER : %s \n ",nom__fichier);
		fprintf(stdout," Impossible d'ouvrir le fichier demandé\n ");
			   exit(EXIT_FAILURE);
		}
                 // Fin de la vérification
	   
	  fprintf(stdout, "Envoi du fichier\n");
	 
		
	 do 
	  {
	  caractere_actuel = fgetc(fichier_envoy);
	  //fgets(caractere_actuel,2000000,fichier_envoy);
          write(sock_connecte, &caractere_actuel ,sizeof(int));
          }
          while(caractere_actuel != EOF);
	  fprintf(stdout, " Connexion terminée avec un client\n");
	
	  fclose(fichier_envoy);

	}


// Création d'une socket  côté serveur
int   cree_socket_stream(const char * nom_hote,const char * nom_service, 
                             const char * nom_proto)
{
	int sock;
	struct sockaddr_in adresse;
	struct hostent * hostent;
	struct servent * servent;
	struct protoent * protoent;
	
	 
	if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) 
	{
	perror("socket erreur de créaion");
	return -1;
	}
	
	memset(& adresse, 0, sizeof (struct sockaddr_in));
	adresse.sin_family = AF_INET;
	//adresse.sin_port = servent->s_port;
	adresse.sin_port = htons(5555);
	adresse.sin_addr.s_addr = htonl(INADDR_ANY);
	//adresse.sin_addr.s_addr = ((struct in_addr *) (hostent->h_addr))->s_addr;
	

if( bind(sock, (struct sockaddr *) & adresse,sizeof(adresse)) <0)      
        {
	close(sock);
	perror("Error in bind");
	return -1;
	}
	
	return sock;
	}
	
	
// Fonction utilisant getsockname pour récupérer les infos de la socket attribuées automatiquement
	
		int affiche_adresse_socket (int sock)
		{
				struct sockaddr_in adresse;
				socklen_t longueur ;
				longueur = sizeof(struct sockaddr_in);
				if (getsockname(sock,(struct sockaddr *) & adresse, & longueur) < 0)
				 {
					perror("getsockname");
						return -1;
				 }
		fprintf(stdout,"IP = %s, Port = %u\n",inet_ntoa(adresse.sin_addr),ntohs(adresse.sin_port));
				return 0;
		}
		
		
// Renvoit toujours la valeur nulle		
int quitter_le_serveur()
{
 return 0;
}

