#include "data_structures.h"

// Programa simples para compilar e verificar se as structs funcionam

int main() {
    NodeOwner* ownersList = NULL; // lista vazia

    // Exemplo: criar 1 Owner "à mão"
    NodeOwner* newOwnerNode = (NodeOwner*) malloc(sizeof(NodeOwner));
    newOwnerNode->owner.taxId = 12345678;
    strcpy(newOwnerNode->owner.name, "John_Smith");
    strcpy(newOwnerNode->owner.postalCode, "6200");
    newOwnerNode->next = NULL;

    // Inserir na lista
    ownersList = newOwnerNode;

    // Só para exemplo: imprimir
    printf("Owner's taxId = %d\n", ownersList->owner.taxId);
    printf("Owner's name = %s\n",  ownersList->owner.name);
    printf("Owner's postalCode = %s\n", ownersList->owner.postalCode);

    // Libertar
    free(ownersList);

    return 0;
}
