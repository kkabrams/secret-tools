#include <stdio.h>
#include <libsecret/secret.h>

int main(int argc,char *argv[]) {
    GError *error = NULL;
    SecretService *secretservice;
    SecretCollection* defaultcollection;
    secretservice = secret_service_get_sync(SECRET_SERVICE_LOAD_COLLECTIONS, NULL, &error);
    if(error) {
        printf("Error: %s\n",error->message);
        return 1;
    }
    if(secretservice == NULL) {
        printf("Error: unknown\n");
        return 2;
    }

    defaultcollection = secret_collection_for_alias_sync(secretservice, SECRET_COLLECTION_DEFAULT, SECRET_COLLECTION_NONE, NULL, &error);
    if(error) {
        printf("Error: %s\n",error->message);
        return 3;
    }
    if(defaultcollection == NULL) {
        printf("Error: unknown\n");
        return 4;
    }

    if(secret_collection_get_locked(defaultcollection)) {
	printf("locked\n");
    } else {
        printf("unlocked\n");
        return 5;
    }
    return 0;
}

