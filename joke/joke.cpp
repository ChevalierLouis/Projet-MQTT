#include <iostream>
#include "mqtt/client.h"

using namespace std;

// Définition des constantes pour l'adresse du serveur MQTT, l'identifiant client et le topic
const string SERVER_ADDRESS("broker.emqx.io:1883");
const string CLIENT_ID("Louis3"); 
const string TOPIC("/ynov/bordeaux/"); 

// Définition de la classe Callback qui sera appelée pour traiter les messages MQTT reçus
class Callback : public virtual mqtt::callback
{
public:
    // Cette méthode est appelée lorsque la connexion MQTT est perdue
    virtual void connection_lost(const string& cause) override {}

    // Cette méthode est appelée lorsque l'envoi d'un message MQTT est terminé
    virtual void delivery_complete(mqtt::delivery_token_ptr token) override {}

    // Cette méthode est appelée lorsqu'un nouveau message MQTT est reçu
    virtual void message_arrived(mqtt::const_message_ptr msg) override
    {
        // Conversion du message en string
        string payload = msg->to_string();

        // Si le message se termine par "qui" (ignorant les espaces) et qu'il a une longueur d'au moins 3 caractères
        if(payload.rfind("qui") == (payload.length()-3) && (payload.length() >= 3)) {

            // Affichage du message reçu
            cout << "Message reçu: " << payload << endl;

            // Envoi d'un nouveau message MQTT en réponse
            mqtt_client_->publish(mqtt::make_message(TOPIC, "quette"));
        }
    }

    // Cette méthode permet de définir le client MQTT à utiliser pour envoyer des messages
    void set_client(mqtt::async_client* cli) { mqtt_client_ = cli; }

private:
    mqtt::async_client* mqtt_client_;
};

// Fonction principale du programme
int main(int argc, char* argv[])
{
    // Création du client MQTT
    mqtt::async_client client(SERVER_ADDRESS, CLIENT_ID);

    // Création de la classe Callback et association du client MQTT à utiliser
    Callback cb;
    cb.set_client(&client);

    // Configuration de la Callback pour le client MQTT
    client.set_callback(cb);

    // Configuration des options de connexion
    mqtt::connect_options options;
    options.set_keep_alive_interval(20);
    options.set_clean_session(true);

    try {
        // Connexion au serveur MQTT
        cout << "Connexion au serveur MQTT en cours..." << flush;
        mqtt::token_ptr conntok = client.connect(options);
        conntok->wait();
        cout << "OK" << endl;

        // Souscription au topic MQTT
        cout << "Souscription au topic '" << TOPIC << "'..." << flush;
        mqtt::token_ptr subtok = client.subscribe(TOPIC, 0);
        subtok->wait();
        cout << "OK" << endl;

        // Boucle infinie pour que le programme continue d'écouter les messages MQTT
        while (true){}
    }
    catch (const mqtt::exception& exc)
    {
        // En cas d'erreur, affichage du message d'erreur et sortie du programme avec le code d'erreur 1
        cerr << "Erreur: " << exc.what() << endl;
        return 1;
    }
    return 0;
}
