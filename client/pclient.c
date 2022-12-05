#include <sys/select.h>
#include <stdlib.h>
#include <stdio.h>
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
int   cree_socket_stream() ;


int main(int  par,const char * fichier[])
{

FILE * fichier_recu=NULL;
int sock_client;
char nom_fichier[100]="Client_";
 
// Communication avec le serveur
struct sockaddr_in serv_addr;
serv_addr.sin_family = AF_INET;
serv_addr.sin_port = htons(5555);
//serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
serv_addr.sin_addr.s_addr = inet_addr(fichier[2]);
// Fin de la configuration de la socket	

fprintf(stdout," %d \n",par);
fprintf(stdout," %s \n",fichier[1]);

	
fprintf(stdout, " Demarrage du client\n ");
if ((sock_client= cree_socket_stream()) < 0)
		exit(EXIT_FAILURE) ;		
if ((affiche_adresse_socket (sock_client)) != 0) 
      exit(EXIT_FAILURE);
      
      
fprintf(stdout, " \n Tentative de Connection au serveur\n ");
if(connect (sock_client,(struct sockaddr *) & serv_addr,sizeof(serv_addr))<0)
	 {
	    printf("\n Error: Connect Failed (%d) --Adresse IP non valide \n", errno);
	    return -1;
	 }

// Pour dfifférencier les fichiers	
if  (fopen(fichier[1],"r") != NULL)
{ 
strcat(nom_fichier,fichier[1]);  // Mise à jour du nom du fichier inutile si le 															
								 //	fichier se trouvait dans un dossier different
fichier_recu=fopen( (const char *) nom_fichier,"w");
}
else 
fichier_recu=fopen(fichier[1],"w");


    // Envoi du nom du fichier
 write(sock_client,fichier[1] ,sizeof(char)*14);
   // Fin 
   
   int buffer;
   
   while(buffer != EOF) 
	  {
         read(sock_client,&buffer,sizeof(int));
       
         fputc(buffer,fichier_recu);
          }
   
   //buffer[21] = '\0';
   //printf("%s\n", buffer);
   
  
   printf("end %d\n",sock_client);
   return 0;
   fclose(fichier_recu);
}











// Création d'une socke côté client
int   cree_socket_stream()   // (const char * nom_hote,const char * nom_service, 
                             //const char * nom_proto)
{
	int sock;
	struct sockaddr_in adresse;
	
	
	/*struct hostent * hostent;
	struct servent * servent;
	struct protoent * protoent;
	
	if ((hostent = gethostname(nom_hote)) == NULL) 
	{
	perror("gethostbyname");
	return -1;
	}
	
	if ((protoent = getprotobyname(nom_proto,NULL)) == NULL) 
	{
	perror("getprotobyname");
	return -1;
	}
	
	if ((servent = getservbyname(nom_service,protoent->p_name)) == NULL)
	 {
	perror("getservbyname");
	return -1;
	 }
	 */
	 
	if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) 
	{
	perror("socket");
	return -1;
	}
	
	memset(& adresse, 0, sizeof (struct sockaddr_in));
	adresse.sin_family = AF_INET;
	//adresse.sin_port = servent->s_port;
	adresse.sin_port = htons(0);
	adresse.sin_port =4444;
	//7.0.0.1")
	adresse.sin_addr.s_addr = inet_addr("127.0.0.1 ");
	//adresse.sin_addr . s_addr = ((struct in_addr *) (hostent->h_addr))>s_addr;
	

if( bind(sock, (struct sockaddr *) & adresse,sizeof(struct sockaddr_in)) <0)      
        {
	close(sock);
	perror("bind");
	return -1;
	}
	
	return sock;
	}
	
	
	
	
	
	
int affiche_adresse_socket (int sock)
{
		struct sockaddr_in adresse;
		socklen_t longueur ;
		longueur = sizeof(struct sockaddr_in);
		if (getsockname(sock,(struct sockaddr *) & adresse, & longueur) < 0)
		 {
			perror("Erreur getsockname");
				return -1;
		 }
fprintf(stdout,"IP = %s, Port = %u\n",inet_ntoa(adresse.sin_addr),ntohs(adresse.sin_port));
		return 0;
}
	
	
	
	

