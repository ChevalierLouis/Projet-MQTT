#include <iostream>
#include <mqtt/async_client.h>
using namespace std;

// Définition des constantes pour l'adresse du serveur MQTT, l'identifiant client et le topic
const string SERVER_ADDRESS("broker.emqx.io:1883");
const string CLIENT_ID("Louis1");
const string TOPIC("/ynov/bordeaux/");

int main(int argc, char *argv[])
{
   	// Création d'un objet client MQTT asynchrone
    mqtt::async_client client(SERVER_ADDRESS, CLIENT_ID);

   	// Configuration des options de connexion
    mqtt::connect_options options;
    options.set_clean_session(true);

   	// Tentative de connexion au serveur MQTT
    cout << "Connexion au serveur MQTT en cours..." << flush;
    mqtt::token_ptr conntol = client.connect(options);
    conntol->wait();	// Attente de la connexion
    cout << "OK" << endl;

   	// Boucle principale pour la saisie et l'envoi des messages
    while (true)
    {
        try
        {
           	// Lecture du message à envoyer depuis l'entrée standard
            string payload;
            cout << "Entrez le message à envoyer: ";
            getline(cin, payload);

           	// Création de l'objet message MQTT
            mqtt::message_ptr pubmsg = mqtt::make_message(TOPIC, payload);

           	// Envoi du message
            client.publish(pubmsg)->wait();	// Attente de la publication
        }

       	// Gestion des exceptions levées par la bibliothèque MQTT
        catch (const mqtt::exception &exc)
        {
            cerr << "Erreur: " << exc.what() << endl;

           	// Déconnexion du client
            client.disconnect()->wait();
            return 1;
        }
    }

   	// Message de confirmation
    cout << "Message publié avec succès !" << endl;

    return 0;
}