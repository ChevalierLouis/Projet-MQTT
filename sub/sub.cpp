#include <iostream>
#include <mqtt/client.h>

using namespace std;

// Définition des constantes pour l'adresse du serveur MQTT, l'identifiant client et le topic
const string SERVER_ADDRESS("broker.emqx.io:1883");
const string CLIENT_ID("Louis2");
const string TOPIC("/ynov/bordeaux/");

class Callback : public virtual mqtt::callback {
public:
    // La méthode message_arrived est appelée lorsqu'un nouveau message est reçu sur le topic auquel le client est abonné
    void message_arrived(mqtt::const_message_ptr msg) override {
        cout << "Message received: " << msg->to_string() << endl;
    }
};

int main() {
    // Création du client MQTT en spécifiant l'adresse du broker et l'ID du client
    mqtt::client client(SERVER_ADDRESS, CLIENT_ID);

    // Configuration des options de connexion
    mqtt::connect_options options;
    options.set_keep_alive_interval(20);
    options.set_clean_session(true);

    // Création d'un objet Callback pour gérer les événements liés au client MQTT
    Callback cb;

    // Configuration du callback pour le client MQTT
    client.set_callback(cb);

    try {
        // Connexion au broker MQTT
        cout << "Connexion au serveur MQTT en cours..." << flush;
        client.connect(options);
        cout << "OK" << endl;

        // Abonnement au topic spécifié
        cout << "Souscription au topic '" << TOPIC << "'..." << flush;
        client.subscribe(TOPIC, 0);
        cout << "OK" << endl;

        // Boucle infinie pour maintenir le client MQTT connecté et traiter les événements
        while (true) {
        }

        // Déconnexion du broker MQTT
        client.disconnect();
    } catch (const mqtt::exception& exc) {
        cerr << "Erreur: " << exc.what() << endl;
        return 1;
    }

    return 0;
}
