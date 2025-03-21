
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
// Structure to represent a parking space
struct ParkingSpace {
    int spaceNumber;
    bool occupied;
    struct ParkingSpace* left;
    struct ParkingSpace* right;
};

// Function to create a new parking space node
struct ParkingSpace* createParkingSpace(int spaceNumber) {
    struct ParkingSpace* newSpace = (struct ParkingSpace*)malloc(sizeof(struct ParkingSpace));
    newSpace->spaceNumber = spaceNumber;
    newSpace->occupied = false;
    newSpace->left = NULL;
    newSpace->right = NULL;
    return newSpace;
}

// Function to insert a parking space into the parking lot tree
struct ParkingSpace* insertParkingSpace(struct ParkingSpace* root, int spaceNumber) {
    if (root == NULL) {
        return createParkingSpace(spaceNumber);
    }

    if (spaceNumber < root->spaceNumber) {
        root->left = insertParkingSpace(root->left, spaceNumber);
    } else if (spaceNumber > root->spaceNumber) {
        root->right = insertParkingSpace(root->right, spaceNumber);
    }

    return root;
}

// Function to display the current status of the parking lot
void displayParkingLot(struct ParkingSpace* root) {
    if (root != NULL) {
        displayParkingLot(root->left);
        printf("Space %d: %s\n", root->spaceNumber, 
               root->occupied ? "Occupied" : "Available");
        displayParkingLot(root->right);
    }
}

// Function to find the minimum parking space in the parking lot tree
struct ParkingSpace* findMin(struct ParkingSpace* root) {
    while (root->left != NULL) {
        root = root->left;
    }
    return root;
}

// Function to remove a parking space from the parking lot tree
struct ParkingSpace* removeParkingSpace(struct ParkingSpace* root, int spaceNumber) {
    if (root == NULL) {
        return root;
    }

    if (spaceNumber < root->spaceNumber) {
        root->left = removeParkingSpace(root->left, spaceNumber);
    } else if (spaceNumber > root->spaceNumber) {
        root->right = removeParkingSpace(root->right, spaceNumber);
    } else {
        if (root->left == NULL) {
            struct ParkingSpace* temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            struct ParkingSpace* temp = root->left;
            free(root);
            return temp;
        }

        struct ParkingSpace* temp = findMin(root->right);
        root->spaceNumber = temp->spaceNumber;
        root->right = removeParkingSpace(root->right, temp->spaceNumber);
    }

    return root;
}

// Function to park a vehicle in the parking lot
void parkVehicle(struct ParkingSpace* root, int spaceNumber) {
    struct ParkingSpace* space = findMin(root);
    while (space != NULL && space->occupied) {
        space = space->right;
    }

    if (space != NULL) {
        space->occupied = true;
        printf("Vehicle parked in space %d\n", space->spaceNumber);
    } else {
        printf("Sorry, the parking lot is full.\n");
    }
}

// Function to remove a vehicle from the parking lot
void removeVehicle(struct ParkingSpace* root, int spaceNumber) {
    struct ParkingSpace* space = findMin(root);
    while (space != NULL && space->spaceNumber != spaceNumber) {
        space = space->right;
    }

    if (space != NULL && space->occupied) {
        space->occupied = false;
        printf("Vehicle removed from space %d\n", space->spaceNumber);
    } else {
        printf("Invalid space number or space is already empty.\n");
    }
}

// Function to free the allocated memory for the parking lot
void freeParkingLot(struct ParkingSpace* root) {
    if (root != NULL) {
        freeParkingLot(root->left);
        freeParkingLot(root->right);
        free(root);
    }
}

int main() {
    struct ParkingSpace* parkingLot = NULL;
    int option, spaceNumber;

    do {
        printf("\nParking Management System\n");
        printf("1. Display Parking Lot\n");
        printf("2. Park Vehicle\n");
        printf("3. Remove Vehicle\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &option);

        switch (option) {
            case 1:
                displayParkingLot(parkingLot);
                break;
            case 2:
                printf("Enter the space number to park the vehicle: ");
                scanf("%d", &spaceNumber);
                parkingLot = insertParkingSpace(parkingLot, spaceNumber);
                parkVehicle(parkingLot, spaceNumber);
                break;
            case 3:
                printf("Enter the space number to remove the vehicle: ");
                scanf("%d", &spaceNumber);
                removeVehicle(parkingLot, spaceNumber);
                break;
            case 4:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid option. Please try again.\n");
        }
    } while (option != 4);

    // Clean up memory
    freeParkingLot(parkingLot);

    return 0;
}