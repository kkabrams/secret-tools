#include <stdio.h>
#include <libsecret/secret.h>

int main(int argc,char *argv[]) {
    GError *error = NULL;
    SecretService *secretservice;
    SecretCollection* defaultcollection;
    GList *objects, *ul;
    gint lock_result;
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
        objects = g_list_append(NULL, defaultcollection);
        lock_result = secret_service_unlock_sync(secretservice,objects,NULL,&ul,&error);
        if (lock_result) {
            printf("Successfully unlocked %d things\n",lock_result);
        } else {
            printf("Error unlocking keyring: %s\n", error->message);
            return 5;
        }
    }
    return 0;
}

