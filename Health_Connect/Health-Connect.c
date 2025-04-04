#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_DOCTORS 100
#define MAX_SPECIALIZATION_LEN 50
#define MAX_SIZE 100
#include <limits.h>


#define MAX_VERTICES 10
#define MAX_HOSPITALS 100
#define INFINITY_COST 9999
#define MAX_NAME_LENGTH 1000
#define MAX_PARAGRAPH_LENGTH 500
#define NUM_MEMBERS 60

typedef struct {
    char name[50];
    int experience;
    char specialization[MAX_SPECIALIZATION_LEN];
    float Rating;
    int d_id;

} Doctor;

typedef struct Node {
    Doctor doctor;
    struct Node* next;
} Node;

struct Member {
    int dr_id;
    char details[MAX_PARAGRAPH_LENGTH];
};

struct feecalc {
    int dr_id,experience, fee;
    char name[50],specialization[50];
    float rating;
};
#define MAX_DOCTORS 100

struct Doctor {
    char name[50];
    float rating;
    int recommendation;
};

void swap(struct Doctor *xp, struct Doctor *yp) {
    struct Doctor temp = *xp;
    *xp = *yp;
    *yp = temp;
}



typedef struct {
    Doctor doctors[MAX_DOCTORS];
    int numDoctors;
     Node* head;
    // Add other graph-related information as needed
} Graph;
Node* createNode(Doctor newDoctor) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->doctor = newDoctor;
    newNode->next = NULL;
    return newNode;
}

void initGraph(Graph* graph) {
    graph->numDoctors = 0;
    graph->head = NULL;
}

void addDoctor(Graph* graph, Doctor newDoctor) {
    Node* newNode = createNode(newDoctor);
    newNode->next = graph->head;
    graph->head = newNode;
    graph->numDoctors++;
}

int BruteForceStringMatch1(char T[], char P[]) {
    int n = strlen(T);
    int m = strlen(P);

    for (int i = 0; i <= n - m; i++) {
        int j = 0;
        while (j < m && P[j] == T[i + j]) {
            j++;
        }
        if (j == m) {
            return i; // Match found at index i
        }
    }

    return -1; // No match found
}

int searchspec(Graph* graph, char spec[], int status) {
    int s = 0;
    Node* current = graph->head;

    while (current != NULL) {
        // Use string matching algorithm to find the specialization
        int matchIndex = BruteForceStringMatch1(current->doctor.specialization, spec);

        if (matchIndex != -1) {
            printf(" Doctor ID: %d Doctor Name: %s Specialization : %s Experience: %d  Rating: %.1lf\n",
                   current->doctor.d_id, current->doctor.name, current->doctor.specialization, current->doctor.experience,current->doctor.Rating);
            s = 1;
        }

        current = current->next;
    }

    return s;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 100

typedef struct {
    char name[50];
    int patientage;
} Patient;

typedef struct {
    char name[50];
} Doctors;

typedef struct {
    Patient patient;
    Doctors doctor;
} Appointment;

typedef struct {
    Appointment data[MAX_SIZE];
    int front, rear;
} Queue;

void initQueue(Queue *q) {
    q->front = -1;
    q->rear = -1;
}

int isEmpty(Queue *q) {
    return (q->front == -1 && q->rear == -1);
}

int isFull(Queue *q) {
    return ((q->rear + 1) % MAX_SIZE == q->front);
}

void enqueue(Queue *q, Appointment appointment) {
    if (isFull(q)) {
        printf("Queue is full. Cannot add more appointments.\n");
        return;
    } else if (isEmpty(q)) {
        q->front = q->rear = 0;
    } else {
        q->rear = (q->rear + 1) % MAX_SIZE;
    }
    q->data[q->rear] = appointment;
    printf("Appointment booked successfully!\n");
}

void dequeue(Queue *q) {
    if (isEmpty(q)) {
        printf("Queue is empty. No appointments to dequeue.\n");
        return;
    } else if (q->front == q->rear) {
        q->front = q->rear = -1;
    } else {
        q->front = (q->front + 1) % MAX_SIZE;
    }
    printf("Appointment removed successfully.\n");
}

void displayAppointments(Queue *q) {
    if (isEmpty(q)) {
        printf("No appointments to display. Queue is empty.\n");
        return;
    }
    printf("Appointments:\n");
    int i = q->front;
    do {
        printf("Patient: %s | Doctor: %s\n", q->data[i].patient.name, q->data[i].doctor.name);
        i = (i + 1) % MAX_SIZE;
    } while (i != (q->rear + 1) % MAX_SIZE);
}

typedef struct Message {
    char sender[100];
    char receiver[100];
    char content[255];
    struct Message *next;
} Message;

typedef struct {
    Message *front;
    Message *rear;
} MessageQueue;

MessageQueue *initializeQueue() {
    MessageQueue *queue = (MessageQueue *)malloc(sizeof(MessageQueue));
    if (queue == NULL) {
        printf("Memory allocation failed for message queue.\n");
        exit(EXIT_FAILURE);
    }

    queue->front = NULL;
    queue->rear = NULL;
    return queue;
}

int isQueueEmpty(MessageQueue *queue) {
    return queue->front == NULL;
}

void enqueueMessage(MessageQueue *queue, const char *sender, const char *receiver, const char *content) {
    Message *newMessage = (Message *)malloc(sizeof(Message));
    if (newMessage == NULL) {
        printf("Memory allocation failed for message.\n");
        exit(EXIT_FAILURE);
    }

    strcpy(newMessage->sender, sender);
    strcpy(newMessage->receiver, receiver);
    strcpy(newMessage->content, content);
    newMessage->next = NULL;

    if (isQueueEmpty(queue)) {
        queue->front = newMessage;
    } else {
        queue->rear->next = newMessage;
    }

    queue->rear = newMessage;
}

void dequeueMessage(MessageQueue *queue) {
    if (!isQueueEmpty(queue)) {
        Message *temp = queue->front;
        queue->front = temp->next;
        free(temp);
    }
}

void displayMessages(MessageQueue *queue) {
    if (isQueueEmpty(queue)) {
        printf("Inbox is empty.\n");
    } else {
        Message *current = queue->front;
        while (current != NULL) {
            printf("To %s from %s: %s\n", current->receiver, current->sender, current->content);
            current = current->next;
        }
    }
}

void cleanupQueue(MessageQueue *queue) {
    while (!isQueueEmpty(queue)) {
        dequeueMessage(queue);
    }

    free(queue);
}

int BruteForceStringMatch(const char *T, const char *P) {
    int n = strlen(T);
    int m = strlen(P);

    for (int i = 0; i <= n - m; i++) {
        int j = 0;
        while (j < m && P[j] == T[i + j]) {
            j++;
        }
        if (j == m) {
            return i;
        }
    }

    return -1;
}

int doctorExists(const char *doctorName) {
    FILE *doctorsFile = fopen("messages.txt", "r");

    if (doctorsFile == NULL) {
        printf("Error opening messages file.\n");
        return 0; // Assume doctor doesn't exist in case of an error
    }

    char line[100]; // Adjust the size based on your needs

    while (fgets(line, sizeof(line), doctorsFile) != NULL) {
        // Remove newline character if present
        line[strcspn(line, "\n")] = '\0';

        if (strcmp(line, doctorName) == 0) {
            fclose(doctorsFile);
            return 1; // Doctor found
        }
    }

    fclose(doctorsFile);
    return 0; // Doctor not found
}

void appointment() {
    Queue appointmentQueue;
    initQueue(&appointmentQueue);

    MessageQueue *inbox = initializeQueue();
    FILE *fp;
    char sender[100];
    char receiver[100];
    char content[255];
    int choice;
int code;
    do {
        printf("\nMenu:\n");
        printf("1. Book an appointment\n");
        printf("2. Cancel an appointment\n");
        printf("3. Display all appointments\n");
        printf("4. Send A Message To Your Doctor\n");
        printf("5. View Messages AS A Doctor\n");
        printf("6. Send Message To Patients\n");
        printf("7. View Messages From Doctor\n");
        printf("8. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
           case 1: {
    fp = fopen("appointment.txt", "a");

    if (fp == NULL) {
        printf("Error\n");
        return 1;
    }

    Appointment newAppointment;
    printf("Enter doctor name: ");
    scanf("%s", newAppointment.doctor.name);
    fprintf(fp, "\nDoctor: %s", newAppointment.doctor.name);

    printf("Enter patient name: ");
    scanf("%s", newAppointment.patient.name);
    fprintf(fp, "\nPatient: %s", newAppointment.patient.name);

    printf("Enter patient age: ");
    scanf("%d", &newAppointment.patient.patientage);
    fprintf(fp, "\nAge: %d", newAppointment.patient.patientage);


    fclose(fp);

    // Enqueue the appointment
    enqueue(&appointmentQueue, newAppointment);
    break;
}
case 2: {
    char doctorName[100];
    char patientName[100];
    printf("Enter doctor's name: ");
    scanf("%s", doctorName);
    printf("Enter patient's name: ");
    scanf("%s", patientName);

    FILE *tempFile = fopen("temp.txt", "w");
    if (tempFile == NULL) {
        printf("Error\n");
        return 1;
    }

    fp = fopen("appointment.txt", "r");
    if (fp == NULL) {
        printf("Error\n");
        return 1;
    }

    int found = 0;
    Appointment appointment;

    while (fscanf(fp, "\nDoctor: %s\nPatient: %s\nAge: %d", appointment.doctor.name, appointment.patient.name, &appointment.patient.patientage) != EOF) {
        if (strcmp(appointment.doctor.name, doctorName) == 0 && strcmp(appointment.patient.name, patientName) == 0) {
            found = 1;
            printf("Appointment found and canceled.\n");
        } else {
            fprintf(tempFile, "\nDoctor: %s\nPatient: %s\nAge: %d", appointment.doctor.name, appointment.patient.name, appointment.patient.patientage);
        }
    }

    fclose(fp);
    fclose(tempFile);

    if (remove("appointment.txt") == 0) {
        if (rename("temp.txt", "appointment.txt") != 0) {
            printf("Error renaming file.\n");
            return 1;
        }
    } else {
        printf("Error deleting appointment.\n");
        return 1;
    }

    if (!found) {
        printf("Appointment not found.\n");
    }

    // Dequeue the canceled appointment if found
    if (found) {
        dequeue(&appointmentQueue);
    }
    break;
}


            case 3: {
    char doctorName[100];
    printf("Enter doctor's name: ");
    scanf("%s", doctorName);

    fp = fopen("appointment.txt", "r");
    if (fp == NULL) {
        printf("Error\n");
        return 1;
    }

    int found = 0;
    Appointment appointment;

    printf("\nAppointments for Doctor %s:\n", doctorName);

    while (fscanf(fp, "\nDoctor: %s\nPatient: %s\nAge: %d", appointment.doctor.name, appointment.patient.name, &appointment.patient.patientage) != EOF) {
        if (strcmp(appointment.doctor.name, doctorName) == 0) {
            found = 1;
            printf("\nPatient: %s\nAge: %d\n", appointment.patient.name, appointment.patient.patientage);
        }
    }

    fclose(fp);

    if (!found) {
        printf("No appointments found for Doctor %s.\n", doctorName);
    }
    break;
}
          case 4: {
    fp = fopen("messages.txt", "a");

    if (fp == NULL) {
        printf("Error\n");
        return 1;
    }

    printf("Enter Doctor's name: ");
    scanf("%s", receiver);


    // Check if the doctor exists in the system
    if (doctorExists(receiver)) {
        printf("Enter your name: ");
        scanf("%s", sender);
        fprintf(fp, "\nSender: %s", sender);

        printf("Enter your message: ");
        scanf(" %[^\n]", content);
        fprintf(fp, "\nMessage: %s", content);

        printf("Hey %s, your message is sent to %s.\n", sender, receiver);
        fclose(fp);
        enqueueMessage(inbox, sender, receiver, content);
    } else {
        printf("Doctor %s does not exist.\n", receiver);
        fclose(fp);
    }

    break;
}
case 5:{
 FILE *doctorsFile = fopen("code.txt", "r");
    if (doctorsFile == NULL) {
        printf("ERROR: Could not open doctors file\n");
        return 1;
    }

    // Read doctor names and codes from the file
    int storedCode;
    char storedDoctor[50];
    int doctorFound = 0;

    printf("Enter your doctor code:");
    scanf("%d", &code);

    while (fscanf(doctorsFile, "%d %49s", &storedCode, storedDoctor) == 2) {
        if (code == storedCode) {
            doctorFound = 1;
            break;
        }
    }

    fclose(doctorsFile);

    if (!doctorFound) {
        printf("Invalid doctor code\n");
        return 1;
    }

    // Open the messages file
    fp = fopen("messages.txt", "r");
    if (fp == NULL) {
        printf("ERROR: Could not open messages file\n");
        return 1;
    }

    printf("Enter receiver's name: ");
    scanf("%s", receiver);

    int access = 0;
    char line[255];

    while (fgets(line, sizeof(line), fp) != NULL) {
        // Assuming that the format is "code receiver message"
        int storedCode;
        char storedReceiver[50];

        if (sscanf(line, " %49s",  storedReceiver) == 1) {
            if ( strcmp(receiver, storedReceiver) == 0) {
                access = 1;
                printf("Hello %s! Your messages are:\n", receiver);

                while (fgets(line, sizeof(line), fp) != NULL ) {
                    printf("%s\n", line);
                }

                break;
            }
        }
    }

    if (access == 0) {
        printf("You have no messages or the code/receiver does not match.\n");
    }

    fclose(fp);
    return 0;
}
case 6:{
     FILE *doctorsFile = fopen("code.txt", "r");
    if (doctorsFile == NULL) {
        printf("ERROR: Could not open doctors file\n");
        return 1;
    }

    // Read doctor names and codes from the file
    int storedCode;
    char storedDoctor[50];
    int doctorFound = 0;

    printf("Enter your doctor code:");
    scanf("%d", &code);

    while (fscanf(doctorsFile, "%d %49s", &storedCode, storedDoctor) == 2) {
        if (code == storedCode) {
            doctorFound = 1;
            break;
        }
    }

    fclose(doctorsFile);

    fp = fopen("messages1.txt", "a");

    if (fp == NULL) {
        printf("Error\n");
        return 1;
    }

    printf("Enter Patient's name: ");
    scanf("%s", receiver);
   fprintf(fp, "\nreceiver : %s", receiver);
   {
        printf("Enter your name: ");
        scanf("%s", sender);
        fprintf(fp, "\nSender: %s", sender);

        printf("Enter your message: ");
        scanf(" %[^\n]", content);
        fprintf(fp, "\nMessage: %s", content);

        printf("Hey %s, your message is sent to %s.\n", sender, receiver);
        fclose(fp);
        enqueueMessage(inbox, sender, receiver, content);
    }

        fclose(fp);

    break;
}
case 7: {
    fp = fopen("messages1.txt", "r");

    if (fp == NULL) {
        printf("ERROR: Could not open file messages\n");
        return 1;
    }

    printf("Enter receiver's name: ");
    scanf("%s", receiver);

    int access = 0;
    char line[255];

    while (fgets(line, sizeof(line), fp) != NULL) {
        if (strstr(line, receiver) != NULL) {
            access = 1;
            printf("Hello %s! Your messages are:\n", receiver);

            // Read and print the subsequent lines until the end of file,
            // excluding lines that contain the receiver's name
            while (fgets(line, sizeof(line), fp) != NULL) {
                if (strstr(line, receiver) == NULL) {
                    printf("%s", line);
                }
            }

            break;
        }
    }

    if (access == 0) {
        printf("You have no messages.\n");
    }

    fclose(fp);
    break;
}
  case 8:
                // Clean up the allocated memory
                cleanupQueue(inbox);
                exit(0);
                break;
            default:
                printf("Invalid choice. Please enter a valid option.\n");
        }
    } while (choice != 8);

    return 0;
}


void sortDoctorsByExperience(Doctor doctors[], int numDoctors) {
    quickSort(doctors, 0, numDoctors - 1);
}

void quickSort(Doctor arr[], int low, int high) {
    if (low < high) {
        int pivotIndex = partition(arr, low, high);

        // Recursively sort the sub-arrays
        quickSort(arr, low, pivotIndex - 1);
        quickSort(arr, pivotIndex + 1, high);
    }
}

int partition(Doctor arr[], int low, int high) {
    // Choose the pivot
    int pivot = arr[low].experience;

    // Initialize pointers for the partition process
    int i = low;
    int j = high + 1;

    do {
        // Increment i while the element at arr[i] is greater than the pivot
        do {
            i++;
        } while (arr[i].experience > pivot);

        // Decrement j while the element at arr[j] is less than the pivot
        do {
            j--;
        } while (arr[j].experience < pivot);

        // Swap if i and j have not crossed
        if (i < j) {
            Doctor temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    } while (i < j);

    // Swap the pivot element with the element at index j
    Doctor temp = arr[low];
    arr[low] = arr[j];
    arr[j] = temp;

    // Return the index where the pivot is now located
    return j;
}
void sortDoctorsByRating(Doctor arr[], int n) {
    int i, j;
    Doctor temp;

    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - 1 - i; j++) {
            // Compare ratings and swap if necessary (for ascending order)
            if (arr[j].Rating > arr[j + 1].Rating) {
                // Swap A[j] and A[j+1]
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}



#define MAX_VERTICES 100
#define MAX_clinics 100
#define INFINITY_COST 9999

int global_count1 = 0;

int distance1[MAX_VERTICES];
int path1[MAX_VERTICES];
int visited1[MAX_VERTICES];

typedef struct clinics {
    int index;
    char name[20];
    char specialization[20];
} CLIN;

CLIN clinics[MAX_clinics];

// Function prototypes
void indexing1(int available[global_count1]);
void dijkstras1(int cost[MAX_VERTICES][MAX_VERTICES], int v, int src);
void loadClinic();
void loadAndGraph1(int cost[MAX_VERTICES][MAX_VERTICES], int traffic[MAX_VERTICES][MAX_VERTICES], int v);
void nearestClinic(int available[global_count1]);
void printNearestClinic(int available[global_count1]);

void indexing1(int available[global_count1]) {
    for (int i = 0; i < global_count1; i++) {
        available[i] = clinics[i].index;
    }
}

void dijkstras1(int cost[MAX_VERTICES][MAX_VERTICES], int v, int src) {
    int j;
    visited1[src] = 1;
    for (j = 0; j < v - 1; j++) {
        int min = INT_MAX;
        int u = 0;
        for (int i = 0; i < v; i++) {
            if (visited1[i] == 0 && distance1[i] < min) {
                min = distance1[i];
                u = i;
            }
        }
        visited1[u] = 1;
        for (int i = 0; i < v; i++) {
            if (visited1[i] == 0 && distance1[i] > cost[u][i] + distance1[u]) {
                distance1[i] = cost[u][i] + distance1[u];
                path1[i] = u;
            }
        }
    }
}

void loadClinic() {
    FILE *file = fopen("clinic.txt", "r");
    if (file == NULL) {
        printf("Error opening file clinic");
        exit(1);
    }

    while (fscanf(file, "%d %s %s", &clinics[global_count1].index,
           clinics[global_count1].name, clinics[global_count1].specialization) == 3) {
        global_count1++;
    }

    fclose(file);
}

void loadAndGraph1(int cost[MAX_VERTICES][MAX_VERTICES], int traffic[MAX_VERTICES][MAX_VERTICES], int v) {
    FILE *file = fopen("pathways.txt", "r");
    if (file == NULL) {
        printf("Error opening file pathways");
        exit(1);
    }

    int x, y, w;
    while (fscanf(file, "%d %d %d", &x, &y, &w) == 3) {
        // Check if the specialization matches before updating the graph
        if (strcmp(clinics[x].specialization, clinics[y].specialization) == 0) {
            cost[x][y] = w;
            cost[y][x] = w;
        }
    }

    fclose(file);
}

void nearestClinic(int available[global_count1]) {
    char userSpecialization[20];
    printf("Enter your specialization: ");
    scanf("%s", userSpecialization);

    printf("\nNearest clinics with specialization '%s' from the source:\n", userSpecialization);

    int found = 0;
    for (int i = 0; i < global_count1; i++) {
        if (strcmp(clinics[i].specialization, userSpecialization) == 0) {
            found = 1;
            printf("%s is at a distance1 of %d km\n", clinics[i].name, distance1[available[i]]);
        }
    }

    if (!found) {
        printf("No clinics found with specialization '%s'\n", userSpecialization);
    }
}

void printNearestClinic(int available[global_count1]) {
    printf("\ndistance1s to all clinics:\n");

    for (int i = 0; i < global_count1; i++) {
        printf("%s (%s) is at the distance1 of %d km\n", clinics[i].name, clinics[i].specialization, distance1[available[i]]);
    }

    exit(0);
}

void clinic() {
    const int v = MAX_VERTICES;
    int cost[MAX_VERTICES][MAX_VERTICES];
    int traffic[MAX_VERTICES][MAX_VERTICES];

    for (int i = 0; i < MAX_VERTICES; i++) {
        for (int j = 0; j < MAX_VERTICES; j++) {
            cost[i][j] = (i == j) ? 0 : INFINITY_COST;
            traffic[i][j] = 0;
        }
    }

    loadAndGraph1(cost, traffic, v);
    loadClinic();

    int available[global_count1];
    indexing1(available);

    printf("CHOOSE YOUR LOCATION CODE\n 0-Lingrajnagar\n 1-KLE TECH\n 2-Vidyanagar\n 3-KIMS\n 4-Hosur\n 5-Gokul Road\n 6-Shreya Nagar\n 7-Tolankeri\n 8-Chennamma Circle\n 9-HDMC\n 10-Railway Colony\n 11-Unkal\n 12-Navanagar\n 13-Rayapur\n ");
    int src;
    printf("Enter your location node: ");
    scanf("%d", &src);

    if (src < 0 || src >= v) {
        printf("Invalid source node. Exiting...\n");
        exit(1);
    }

    for (int i = 0; i < v; i++) {
        distance1[i] = cost[src][i];
    }

    for (int i = 0; i < v; i++) {
        path1[i] = src;
    }

    dijkstras1(cost, v, src);

    nearestClinic(available);

return 0;
}


void searchdoc(Graph* doctorGraph) {
    int status = 0;
    char spec[MAX_SPECIALIZATION_LEN];

    printf("\nPediatrician\nGynecologist\nPsychiatrist\nCardiologist\nNeurologist\nPhysicians\nDermatologist\nOphthalmologist\nOrthopaedist\nDentist\nENT\n");

    printf("Enter the required specialization: ");
    scanf("%s", spec);
    status = searchspec(doctorGraph, spec, status);
    if (status == 1) {
        int rch;
        printf("\nEnter 1 to get best recommended and rated DR\n");
        printf("Enter 2 to get the nearest DR\n");
        printf("Enter 3 to get DR with most experience \n");
        scanf("%d", &rch);
        switch (rch) {
             case 1: {
            // Create an array to store doctors with the specified specialization
            Doctor specDoctors[MAX_DOCTORS];
            int numSpecDoctors = 0;

            // Populate the array with doctors matching the specialization
            Node* current = doctorGraph->head;
            while (current != NULL) {
                if (strcmp(current->doctor.specialization, spec) == 0) {
                    specDoctors[numSpecDoctors] = current->doctor;
                    numSpecDoctors++;
                }
                current = current->next;
            }

            // Sort the doctors by rating in descending order
            sortDoctorsByRating(specDoctors, numSpecDoctors);

            // Display doctors in descending order of rating
            printf("\nDoctors sorted by rating (highest to lowest):\n");
            for (int i = numSpecDoctors - 1; i >= 0; i--) {
                printf("Doctor ID: %d Doctor Name: %s Specialization: %s Experience: %d Rating: %.1lf\n",
                       specDoctors[i].d_id, specDoctors[i].name, specDoctors[i].specialization, specDoctors[i].experience, specDoctors[i].Rating);
            }
            break;
        }

            case 2:{
            clinic();
            }

                break;
            case 3: {
                // Create an array to store doctors with the specified specialization
                Doctor specDoctors[MAX_DOCTORS];
                int numSpecDoctors = 0;

                // Populate the array with doctors matching the specialization
                Node* current = doctorGraph->head;
                while (current != NULL) {
                    if (strcmp(current->doctor.specialization, spec) == 0) {
                        specDoctors[numSpecDoctors] = current->doctor;
                        numSpecDoctors++;
                    }
                    current = current->next;
                }

                // Sort the doctors by experience
                sortDoctorsByExperience(specDoctors, numSpecDoctors);

                // Display doctors with most experience
                printf("\nDoctors sorted by experience (highest to lowest):\n");
                for (int i = 0; i < numSpecDoctors; i++) {
                    printf("Doctor ID: %d Doctor Name: %s Specialization: %s Experience: %d\n",
                           specDoctors[i].d_id, specDoctors[i].name, specDoctors[i].specialization, specDoctors[i].experience);
                }
                break;
            }
            default:
                printf("Invalid choice.\n");
        }
    } else {
        printf("No Doctors available\n");
    }
}


void createDoctorFromInput(Graph* doctorGraph) {
    Doctor newDoctor;
    int no_doctors = 60;
    // Assuming you have a file named "doctors.txt" with doctor details in the format: "name experience specialization"
    FILE* theFile = fopen("doctors.txt", "r");
    if (theFile == NULL) {
        printf("Error opening the file doctors.\n");
        exit(1);
    }
   for (int i = 0; i < no_doctors; i++) {
        fscanf(theFile, " %d %s %s %d %f",  &newDoctor.d_id,newDoctor.name,newDoctor.specialization, &newDoctor.experience,&newDoctor.Rating);
        Doctor doctori = newDoctor;
        addDoctor(doctorGraph, doctori);
    }

    fclose(theFile);
}

void read_recomendation() {

    struct Member members[NUM_MEMBERS];


    FILE *file = fopen("rewievs.txt", "r");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }


    for (int i = 0; i < NUM_MEMBERS; ++i) {
        if (fscanf(file, "%d", &members[i].dr_id) != 1) {
            fprintf(stderr, "Error reading dr_id for member %d\n", i + 1);
            break;
        }

        if (fscanf(file, " %[^\n]", members[i].details) != 1) {
            fprintf(stderr, "Error reading details for member %d\n", i + 1);
            break;
        }
    }


    fclose(file);
     int searchDrID;


    printf("Enter the DR ID you want to search\n");
    scanf("%d", &searchDrID);

    int found = 0;
    for (int i = 0; i < NUM_MEMBERS; ++i) {
        if (members[i].dr_id == searchDrID) {
            //printf("\nFound Dr ID %d:\n", searchDrID);
            printf("Reviews: %s\n", members[i].details);
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("\nDr ID %d not found in the entered data.\n", searchDrID);
    }


    return 0;
}


void fee_calculate() {
   struct feecalc dr_fee[NUM_MEMBERS];
    int searchDrID,no_doc = 100;
    // Assuming you have a file named "doctors.txt" with doctor details in the format: "name experience specialization"
    FILE* theFile = fopen("fee.txt", "r");
    if (theFile == NULL) {
        printf("Error opening the file doctors.\n");
        exit(1);
    }
   for (int i = 0; i < no_doc; i++) {
        fscanf(theFile, " %d %s %s %d %f %d",  &dr_fee[i].dr_id,dr_fee[i].name,dr_fee[i].specialization ,&dr_fee[i].experience,&dr_fee[i].rating,&dr_fee[i].fee);
   }

    fclose(theFile);

     printf("\nEnter Dr ID to search FEE: ");
    scanf("%d", &searchDrID);

    int found = 0;
    for (int i = 0; i < NUM_MEMBERS; ++i) {
        if (dr_fee[i].dr_id == searchDrID) {
           // printf("\nFound Dr ID %d:\n", searchDrID);
            printf(" DR ID: %d DR NAME: %s SPECIALISATION:%s FEES FOR CONSULTATION: RS %d",  dr_fee[i].dr_id,dr_fee[i].name,dr_fee[i].specialization ,dr_fee[i].fee);
            found = 1;
            break;  // Exit loop once found
        }
    }

    if (!found) {
        printf("\nDr ID %d not found in the entered data.\n", searchDrID);
    }
}



void patientAction(Graph *doctorGraph) {
    int choice;
    do {
        printf("\nPATIENT MENU:\n");
        printf("1. Search For Doctor\n");
        printf("2. Read Reviews About Doctor \n");
        printf("3. Fee Estimation of Doctor\n");
        printf("4. Book An Appointment\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                searchdoc(doctorGraph);
                break;
                case 2 :{
                 read_recomendation();
                 break;}
                 case 3:{
                 fee_calculate();
                 break;}
            case 4:
                 appointment();
                break;
            case 5:
                printf("Exiting patient actions\n");
                break;
            default:
                printf("Invalid choice. Please enter a valid option.\n");
        }
    } while (choice != 5);
}



///doctor code
void appendDoctorToFile(Graph* doctorGraph) {
    // Assuming the file name is "docdet.txt"
    FILE* theFile = fopen("docdet.txt", "a");
    if (theFile == NULL) {
        printf("Error opening the file doctors.\n");
        exit(1);
    }
    int no_doctors = 1;

    printf("Enter details for each doctor:\n");

    for (int i = 0; i < no_doctors; i++) {
        Doctor currentDoctor;

        // Taking input from the user for each doctor
        printf("Enter details for doctor %d:\n", i + 1);
        printf("Doctor ID: ");
        scanf("%d", &currentDoctor.d_id);

        printf("Doctor Name: ");
        scanf("%s", currentDoctor.name);

        printf("Specialization: ");
        scanf("%s", currentDoctor.specialization);

        printf("Experience: ");
        scanf("%d", &currentDoctor.experience);

        printf("Rating: ");
        scanf("%f", &currentDoctor.Rating);

        // Appending doctor details to the file
        fprintf(theFile, " %d %s %s %d %f\n", currentDoctor.d_id, currentDoctor.name, currentDoctor.specialization, currentDoctor.experience, currentDoctor.Rating);
    }

    fclose(theFile);
}

void deletedoc_file() {
    const char *filename = "docdet.txt";
    int doctorIdToDelete;

    printf("Enter the Doctor ID to delete: ");
    scanf("%d", &doctorIdToDelete);

    FILE *originalFile = fopen(filename, "r");
    FILE *tempFile = fopen("temp.txt", "w");

    if (originalFile == NULL || tempFile == NULL) {
        printf("Error opening files.\n");
        exit(1);
    }

    char line[1000];

    while (fgets(line, sizeof(line), originalFile) != NULL) {

        int currentDoctorId;
        sscanf(line, "%d", &currentDoctorId);

        if (currentDoctorId != doctorIdToDelete) {

            fputs(line, tempFile);
        }
    }

    fclose(originalFile);
    fclose(tempFile);


    if (remove(filename) != 0 || rename("temp.txt", filename) != 0) {
        printf("Error updating the file.\n");
        exit(1);
    }

    printf("Doctor with ID %d deleted successfully.\n", doctorIdToDelete);

}
void precomputeBoyerMoore(const char *needle, int needleLength, int *badCharacter) {
    for (int i = 0; i < 256; i++) {
        badCharacter[i] = needleLength;
    }

    for (int i = 0; i < needleLength - 1; i++) {
        badCharacter[(unsigned char)needle[i]] = needleLength - 1 - i;
    }
}

// Boyer-Moore algorithm for string searching
int boyerMooreSearch(const char *haystack, const char *needle) {
    int haystackLength = strlen(haystack);
    int needleLength = strlen(needle);

    int badCharacter[256];
    precomputeBoyerMoore(needle, needleLength, badCharacter);

    int i = needleLength - 1; // Index in haystack
    int j = needleLength - 1; // Index in needle

    while (i < haystackLength) {
        if (needle[j] == haystack[i]) {
            if (j == 0) {
                return i; // Match found
            }
            i--;
            j--;
        } else {
            i += badCharacter[(unsigned char)haystack[i]] - (needleLength - 1) + j;
            j = needleLength - 1;
        }
    }

    return -1; // Match not found
}

void searchDoctorByPrefix(const char *filename, const char *prefix) {
    FILE *file = fopen(filename, "r");
    int indexans;

    if (file == NULL) {
        printf("Error opening the file %s.\n", filename);
        exit(1);
    }

    char line[MAX_NAME_LENGTH];

    while (fgets(line, sizeof(line), file) != NULL) {
        // Assuming the doctor name is the second word in each line
        char currentDoctorName[MAX_NAME_LENGTH];
        sscanf(line, "%*s %s", currentDoctorName);

        int index = boyerMooreSearch(currentDoctorName, prefix);

        if (index != -1) {
            // If the prefix matches the beginning of the doctor name, print the line
            printf("%s", line);
            indexans=1;
        }

    }
    if (!indexans)
            printf("Search not found\n");

    fclose(file);
}
void boyre_more_search() {
    const char *filename = "docdet.txt"; // Replace with your file name
    char prefix[MAX_NAME_LENGTH];

    printf("Enter the Doctor Name prefix to search: ");
    scanf("%s", prefix);

    searchDoctorByPrefix(filename, prefix);

    //return 0;
}
 void listaction()
 {

  int choic;
    do {
        printf("\n 1.To search Doctors \n ");

        printf("2.Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choic);
        switch (choic) {
            case 1:
                boyre_more_search();
                // Implement logic to list all doctors
                break;
                case 2:{

                break;}

            default:
                printf("Invalid choice. Please try again.\n");
        }

    } while (choic != 2);



 }

void DoctorAction(Graph* doctorGraph) {
    int choic;
    do {
        printf("\n 1.List  All Doctors \n ");
        printf("2.TO ADD  A Doctor\n ");
        printf("3.TO DELETE A Doctor\n ");
        printf("4.Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choic);
        switch (choic) {
            case 1:
                // Implement logic to list all doctors
                listaction();
                break;
            case 2:
                // Implement logic to get credentials of a doctor
                appendDoctorToFile(doctorGraph);

                break;
            case 3:
                // Implement logic to get credentials of a doctor
                deletedoc_file();
                break;
            case 4:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }

    } while (choic != 3);
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


// AVL Node
typedef struct AVLNode {
    char labName[50];
    char servicesAvailable[100];
    char location[100];
    char openingTime[10];
    char closingTime[10];
    double patientReview;
    struct AVLNode* left;
    struct AVLNode* right;
    int height;
} AVLNode;

typedef struct MaxHeapNode {
    AVLNode *labNode;
} MaxHeapNode;

typedef struct Edge {
    int u, v;
    double w;
} Edge;

void quicksort(Edge edge[], int low, int high)
 {

}

int find(int arr[], int u, int v)
 {
    return (arr[u] == arr[v]);
}

void union_find(int arr[], int u, int v, int n)
{
    int temp = arr[u];
    for (int i = 0; i < n; i++) {
        if (arr[i] == temp) {
            arr[i] = arr[v];
        }
    }
}

// Get height of a node
int height(AVLNode *node)
{
    if (node == NULL)
        return 0;
    return node->height;
}

// Get balance factor of a node
int getBalance(AVLNode *node)
 {
    if (node == NULL)
        return 0;
    return height(node->left) - height(node->right);
}

// Right rotate subtree rooted with y
AVLNode *rightRotate(AVLNode *y)
{
    AVLNode *x = y->left;
    AVLNode *T2 = x->right;

    // Perform rotation
    x->right = y;
    y->left = T2;

    // Update heights
    y->height = 1 + fmax(height(y->left), height(y->right));
    x->height = 1 + fmax(height(x->left), height(x->right));

    // Return new root
    return x;
}

// Left rotate subtree rooted with x
AVLNode *leftRotate(AVLNode *x)
 {
    AVLNode *y = x->right;
    AVLNode *T2 = y->left;

    // Perform rotation
    y->left = x;
    x->right = T2;

    // Update heights
    x->height = 1 + fmax(height(x->left), height(x->right));
    y->height = 1 + fmax(height(y->left), height(y->right));

    // Return new root
    return y;
}

//Insert a lab into the AVL tree
// Insert a lab into the AVL tree
AVLNode *insert(AVLNode *root, char labName[50], char servicesAvailable[100], char location[100], char openingTime[10], char closingTime[10], double patientReview)
 {
    // Standard BST insert
    if (root == NULL) {
        AVLNode *node = (AVLNode *)malloc(sizeof(AVLNode));
        strcpy(node->labName, labName);
        strcpy(node->servicesAvailable, servicesAvailable);
        strcpy(node->location, location);
        strcpy(node->openingTime, openingTime);
        strcpy(node->closingTime, closingTime);
        node->left = node->right = NULL;
        node->height = 1;
        node->patientReview = patientReview;  // Set patient review
        return node;
    }

    if (strcmp(labName, root->labName) < 0)
        root->left = insert(root->left, labName, servicesAvailable, location, openingTime, closingTime, patientReview);
    else if (strcmp(labName, root->labName) > 0)
        root->right = insert(root->right, labName, servicesAvailable, location, openingTime, closingTime, patientReview);
    else // Duplicate lab names are not allowed
        return root;

    // Update height of current node
    root->height = 1 + fmax(height(root->left), height(root->right));

    // Get balance factor
    int balance = getBalance(root);

    // Left Left Case
    if (balance > 1 && strcmp(labName, root->left->labName) < 0)
        return rightRotate(root);

    // Right Right Case
    if (balance < -1 && strcmp(labName, root->right->labName) > 0)
        return leftRotate(root);

    // Left Right Case
    if (balance > 1 && strcmp(labName, root->left->labName) > 0)
        {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    // Right Left Case
    if (balance < -1 && strcmp(labName, root->right->labName) < 0)
        {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}


// Search for a lab by name in the AVL tree
void badCharHeuristic(char *str, int size, int badchar[256])
{
    int i;

    for (i = 0; i < 256; i++)
        badchar[i] = -1;

    for (i = 0; i < size; i++)
        badchar[(int) str[i]] = i;
}

// Boyer-Moore search algorithm
AVLNode *searchBoyerMoore(AVLNode *root, char pattern[50])
 {
    int m = strlen(pattern);
    int n;

    while (root != NULL) {
        n = strlen(root->location);  // Change: Use location instead of labName

        int badchar[256];
        badCharHeuristic(pattern, m, badchar);

        int s = 0;
        while (s <= (n - m)) {
            int j = m - 1;

            while (j >= 0 && pattern[j] == root->location[s + j])  // Change: Use location instead of labName
                j--;

            if (j < 0)
                {
                // Pattern found, return the current node
                return root;
                }
            else
            {
                // Shift the pattern based on bad character heuristic
                s += (j - badchar[(int)root->location[s + j]]);  // Change: Use location instead of labName
            }
        }

        // Move to the next node based on BST property
        if (strcmp(pattern, root->location) < 0)  // Change: Use location instead of labName
            root = root->left;
        else
            root = root->right;
    }

    // Pattern not found, return NULL
    return NULL;
}
// Modified search function using Boyer-Moore algorithm
AVLNode *search(AVLNode *root, char labName[50])
{
    return searchBoyerMoore(root, labName);
}
// Inorder traversal of the AVL tree
void inorderTraversal(AVLNode *root)
 {
    if (root != NULL) {
        inorderTraversal(root->left);
        printf("Lab Name: %s, Services: %s, Location: %s\n", root->labName, root->servicesAvailable, root->location);
        inorderTraversal(root->right);
    }
}

// Register a new lab with opening and closing times
AVLNode *registerLab(AVLNode *root)
 {
    char labName[50];
    char servicesAvailable[100];
    char location[100];
    char openingTime[10];  // Added opening time
    char closingTime[10];  // Added closing time
    double patientReview;

    printf("Enter Lab Name: ");
    scanf("%s", labName);

    // Check if lab already exists
    if (search(root, labName) != NULL)
        {
        printf("Lab with the same name already exists.\n");
        return root;
    }

    printf("Enter Services Available: ");
    scanf("%s", servicesAvailable);

    printf("Enter Location: ");
    scanf("%s", location);

    printf("Enter Opening Time (HH:MM): ");
    scanf("%s", openingTime);

    printf("Enter Closing Time (HH:MM): ");
    scanf("%s", closingTime);

    printf("Enter Patient Review (out of 10): ");
    scanf("%lf", &patientReview);


    // Insert new lab into AVL tree with opening and closing times
    root = insert(root, labName, servicesAvailable, location, openingTime, closingTime,patientReview);

    printf("Lab registered successfully!\n");

    return root;
}
// Count the number of nodes in the AVL tree
int countNodes(AVLNode *root)
 {
    if (root == NULL)
        return 0;
    return 1 + countNodes(root->left) + countNodes(root->right);
}

// Display the number of labs present in the AVL tree
void displayLabCount(AVLNode *root)
{
    int count = countNodes(root);
    printf("Number of Labs Present: %d\n", count);
}

// Display details of all registered labs in the AVL tree



// ... (previous code)

// ... (previous code)

void maxHeapify(MaxHeapNode arr[], int n, int i)
 {
    // Implementation (same as before)
}

// Function to build a max heap
void buildMaxHeap(MaxHeapNode arr[], int n) {
    // Implementation (same as before)
}

// Function to perform heap sort
void heapSort(MaxHeapNode arr[], int n) {
    // Implementation (same as before)
}

void displayAllLabsHeapSortByReviews(AVLNode *root) {
    // Count the number of labs
    int count = countNodes(root);

    // Create an array to store the nodes
    AVLNode *labArray[count];
    int index = 0;

    // Inorder traversal to populate the array
    void inorderToArray(AVLNode *node) {
        if (node != NULL) {
            inorderToArray(node->left);
            labArray[index++] = node;
            inorderToArray(node->right);
        }
    }

    inorderToArray(root);

    // Create a max heap node array
    MaxHeapNode maxHeapArray[count];
    for (int i = 0; i < count; i++) {
        maxHeapArray[i].labNode = labArray[i];
    }

    // Build max heap
    buildMaxHeap(maxHeapArray, count);

    // Perform heap sort
    heapSort(maxHeapArray, count);

    // Display the sorted labs with patient reviews
    printf("\nRegistered Labs (Sorted by Patient Reviews using Heap Sort):\n");
    for (int i = 0; i < count; i++) {
        printf("Lab Name: %s, Services: %s, Location: %s, Patient Review: %.2f\n",
               maxHeapArray[i].labNode->labName, maxHeapArray[i].labNode->servicesAvailable,
               maxHeapArray[i].labNode->location, maxHeapArray[i].labNode->patientReview);
    }
}




// Merge two sorted arrays based on opening time
void merge(AVLNode *arr[], int left, int mid, int right)
{
    int i, j, k;
    int n1 = mid - left + 1;
    int n2 = right - mid;

    // Create temporary arrays
    AVLNode *L[n1];
    AVLNode *R[n2];

    // Copy data to temporary arrays L[] and R[]
    for (i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    // Merge the temporary arrays back into arr[left..right] based on opening time
    i = 0;
    j = 0;
    k = left;
    while (i < n1 && j < n2)
        {
        // Compare opening times (assuming openingTime is in "HH:MM" format)
        if (strcmp(L[i]->openingTime, R[j]->openingTime) <= 0)
        {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    // Copy the remaining elements of L[], if there are any
    while (i < n1)
        {
        arr[k] = L[i];
        i++;
        k++;
    }

    // Copy the remaining elements of R[], if there are any
    while (j < n2)
        {
        arr[k] = R[j];
        j++;
        k++;
    }
}

// Mergesort based on opening time
void mergeSort(AVLNode *arr[], int left, int right)
{
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}


// Display details of all registered labs sorted by location
void displayAllLabs(AVLNode *root)
{
    printf("\nRegistered Labs (Sorted by Location):\n");

    // Count the number of labs
    int count = countNodes(root);

    // Create an array to store the nodes
    AVLNode *labArray[count];
    int index = 0;

    // Inorder traversal to populate the array
    void inorderToArray(AVLNode *node) {
        if (node != NULL) {
            inorderToArray(node->left);
            labArray[index++] = node;
            inorderToArray(node->right);
        }
    }

    inorderToArray(root);

    // Perform mergesort based on location
    mergeSort(labArray, 0, count - 1);
 // Display the sorted labs with patient reviews
    for (int i = 0; i < count; i++)
        {
        printf("Lab Name: %s, Services: %s, Location: %s, Patient Review: %.2f\n",
               labArray[i]->labName, labArray[i]->servicesAvailable, labArray[i]->location, labArray[i]->patientReview);
    }
}

// ... (rest of the code)





    // Existing AVL insertion code (unchanged)
    // ...


// Your other AVL tree functions go here...

void LabPersonnalAction()

{

    printf("                                         WELCOME -- TO -- LABORATORY -- SECTION\n");
    printf("\n");
    printf("\n");
    AVLNode* root = NULL;

    int choice1;
    do {
        printf("\n1. Register Lab\n");
        printf("2. Search Lab\n");
        printf("3. Display Number of Labs\n");
        printf("4. Display All Registered Labs\n");
        printf("5. Calculate Minimum Spanning Tree Weight\n");
        printf("6. Display All Registered Labs.\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice1);

        switch (choice1) {
            case 1:
                root = registerLab(root);
                break;
            case 2: {
                char searchLabName[50];
                printf("Enter the location to search: ");
                scanf("%s", searchLabName);

                AVLNode* foundLab = search(root, searchLabName);

                if (foundLab != NULL)
                {
                    printf("Lab found!\n");
                    printf("Lab Name: %s, Services: %s, Location: %s\n", foundLab->labName, foundLab->servicesAvailable, foundLab->location);
                } else
                {
                    printf("Lab not found!\n");
                }
                break;
            }
            case 3:
                displayLabCount(root);
                break;
            case 4:
                displayAllLabs(root);
                break;
            case 5:
                {
                    int e;
                    double sum = 0;
                    printf("Enter the number of edges: ");
                    scanf("%d", &e);

                    Edge* edge = (Edge*)malloc(e * sizeof(Edge));

                    printf("Enter edges (u v w):\n");
                    for (int i = 0; i < e; i++)
                    {
                        scanf("%d %d %lf", &edge[i].u, &edge[i].v, &edge[i].w);
                    }

                    quicksort(edge, 0, e - 1);

                    int ver;
                    printf("Enter the number of vertices: ");
                    scanf("%d", &ver);

                    int* arr = (int*)malloc(ver * sizeof(int));
                    for (int i = 0; i < ver; i++)
                    {
                        arr[i] = i;
                    }

                    int findee;
                    for (int i = 0; i < e; i++)
                    {
                        findee = find(arr, edge[i].u, edge[i].v);
                        if (!findee) {
                            union_find(arr, edge[i].u, edge[i].v, ver);
                            sum += edge[i].w;
                        }
                    }

                    printf("Minimum Spanning Tree Weight: %lf\n", sum);

                    free(edge);
                    free(arr);
                }
                break;
            case 6:
                {
                    displayAllLabsHeapSortByReviews(root);
                    break;
                }
            case 7:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice1 != 6);



return 0;
}


#include <stdio.h>
#include <limits.h>
#include <stdlib.h>

#define MAX_VERTICES 100
#define MAX_pharma 100
#define INFINITY_COST 9999
#define MAX_NAME_SIZE 15
int global_count2 = 0;

int distance2[MAX_VERTICES];
int path2[MAX_VERTICES];
int visited2[MAX_VERTICES];

typedef struct pharma {
    int index;
    char name[20];
    int discount;
} PHAR;

PHAR pharma[MAX_pharma];

// Function prototypes
void indexing2(int available[global_count2]);
void dijkstras2(int cost[MAX_VERTICES][MAX_VERTICES], int v, int src);
void loadpharma();
void loadAndGraph2(int cost[MAX_VERTICES][MAX_VERTICES], int v);
void nearestpharma(int available[global_count2]);
void printnearestpharma(int available[global_count2]);
int chooseNearestPharmacy(int available[global_count2]);
int findMaxDiscountPharmacy1(int available[global_count2], int temp);

void indexing2(int available[global_count2]) {
    for (int i = 0; i < global_count2; i++) {
        available[i] = pharma[i].index;
    }
}

void dijkstras2(int cost[MAX_VERTICES][MAX_VERTICES], int v, int src) {
    int j;
    visited2[src] = 1;
    for (j = 0; j < v - 1; j++) {
        int min = INT_MAX;
        int u = 0;
        for (int i = 0; i < v; i++) {
            if (visited2[i] == 0 && distance2[i] < min) {
                min = distance2[i];
                u = i;
            }
        }
        visited2[u] = 1;
        for (int i = 0; i < v; i++) {
            if (visited2[i] == 0 && distance2[i] > cost[u][i] + distance2[u]) {
                distance2[i] = cost[u][i] + distance2[u];
                path2[i] = u;
            }
        }
    }
}

void loadpharma() {
    FILE *file = fopen("pharma.txt", "r");
    if (file == NULL) {
        printf("Error opening file pharma24");
        exit(1);
    }

    while (fscanf(file, "%d %s %d", &pharma[global_count2].index,
           pharma[global_count2].name, &pharma[global_count2].discount) == 3) {
        global_count2++;
    }

    fclose(file);
}

void loadAndGraph2(int cost[MAX_VERTICES][MAX_VERTICES], int v) {
    FILE *file = fopen("pharpath.txt", "r");
    if (file == NULL) {
        printf("Error opening file path2");
        exit(1);
    }

    int x, y, w;
    while (fscanf(file, "%d %d %d", &x, &y, &w) == 3) {
        cost[x][y] = w;
        cost[y][x] = w;
    }

    fclose(file);
}

void nearestpharma(int available[global_count2]) {
    printf("\nNearest pharma from the source:\n");

    for (int i = 0; i < global_count2; i++) {
        printf("%s is at a distance of %d km provides a discount of %d %%\n", pharma[i].name, distance2[available[i]], pharma[i].discount);
    }
}

void printnearestpharma(int available[global_count2]) {
    printf("\nDistances to all pharma:\n");

    for (int i = 0; i < global_count2; i++) {
        printf("%s is at a distance of %d km provides a discount of %d %%\n", pharma[i].name, distance2[available[i]], pharma[i].discount);
    }
}
int chooseNearestPharmacy(int available[global_count2]) {
    int minDistance = INT_MAX;
    int chosenPharmacy = -1;

    for (int i = 0; i < global_count2; i++) {
        if (distance2[available[i]] < minDistance) {
            minDistance = distance2[available[i]];
            chosenPharmacy = i;
        }
    }

    return chosenPharmacy;
}


int findMaxDiscountPharmacy1(int available[global_count2], int temp)
//uses insertion sort to sort discount values from highest to lowest
{
    for (int i = 1; i < global_count2; i++) {
        struct pharma key = pharma[i];
        int j = i - 1;

        // Move elements of pharma[0..i-1] that are greater than key.discount
        // to one position ahead of their current position
        while (j >= 0 && pharma[j].discount < key.discount) {
            pharma[j + 1] = pharma[j];
            j = j - 1;
        }
        pharma[j + 1] = key;
    }

    // Now the array is sorted in descending order by discount

    // Assuming you want to return the index of the pharmacy with the highest discount
    return 0;
}


void registerPharmacy1() {

    FILE *file1 = fopen("pharma.txt", "a");


    if (file1 == NULL ) {
        printf("Error opening files for registration");
        exit(1);
    }

    printf("\nEnter the name of the new pharmacy: ");
    scanf("%s", pharma[global_count2].name);

    printf("\nEnter the area code of the new pharmacy: ");
    scanf("%d", &pharma[global_count2].index);

    printf("\nEnter discount provided by the pharmacy: ");
    scanf("%d", &pharma[global_count2].discount);

    fprintf(file1, "%d %s %d\n", pharma[global_count2].index, pharma[global_count2].name,
            pharma[global_count2].discount);

    fclose(file1);

    global_count2++;
}

void deletePharmacy1() {
    int deleteIndex;
    char deletename[MAX_NAME_SIZE];

    printf("\nEnter the area code of the pharmacy to delete: ");
    scanf("%d", &deleteIndex);

    printf("Enter the Pharmacy Name: ");
    scanf("%s", deletename);

    // Search for the pharmacy with the specified area code and name
    int foundIndex = -1;
    for (int i = 0; i < global_count2; i++) {
        if (pharma[i].index == deleteIndex && strcmp(pharma[i].name, deletename) == 0) {
            foundIndex = i;
            break;
        }
    }

    // If the pharmacy is found, delete it
    if (foundIndex != -1) {
        // Shift the remaining elements to overwrite the deleted pharmacy
        for (int i = foundIndex; i < global_count2 - 1; i++) {
            pharma[i] = pharma[i + 1];
        }

        // Decrement the global count to reflect the deletion
        global_count2--;

        printf("Pharmacy with area code %d and name %s has been deleted.\n", deleteIndex, deletename);

        // Rewrite the entire array back to both files after the deletion
        FILE *file1 = fopen("pharma.txt", "w");


        if (file1 == NULL ) {
            printf("Error opening files for writing phar");
            exit(1);
        }

        for (int i = 0; i < global_count2; i++) {
            fprintf(file1, "%d %s %d\n", pharma[i].index, pharma[i].name, pharma[i].discount);

        }

        fclose(file1);

    } else {
        printf("Pharmacy with area code %d and name %s not found.\n", deleteIndex, deletename);
    }
}


void pharmareg1() {
    char registerOption;
    printf("\nDo you want to register a new pharmacy? (y/n): ");
    scanf(" %c", &registerOption);

    if(registerOption == 'y' || registerOption == 'Y')

        registerPharmacy1();

        else
{
         exit(0);
}

}


void pharmacy() {
    const int v = MAX_VERTICES;
    int cost[MAX_VERTICES][MAX_VERTICES];

    for (int i = 0; i < MAX_VERTICES; i++) {
        for (int j = 0; j < MAX_VERTICES; j++) {
            cost[i][j] = (i == j) ? 0 : INFINITY_COST;
        }
    }

    loadAndGraph2(cost, v);
    loadpharma();

    int available[global_count2];
    indexing2(available);
printf(" CHOSE YOUR AREA CODE:\n 0-Lingrajnagar\n 1-KLE TECH\n 2-Vidyanagar\n 3-KIMS\n 4-Hosur\n 5-Gokul Road\n 6-Shreya Nagar\n 7-Tolankeri\n 8-Chennamma Circle\n 9-HDMC\n 10-Railway Colony\n 11-Unkal\n 12-Navanagar\n 13-Rayapur\n 14-Old Hubli\n");

    int src;
    printf("Enter your location node: ");
    scanf("%d", &src);

    if (src < 0 || src >= v) {
        printf("Invalid source node. Exiting...\n");
        exit(1);
    }

    for (int i = 0; i < v; i++) {
        distance2[i] = cost[src][i];
    }

    for (int i = 0; i < v; i++) {
        path2[i] = src;
    }

    dijkstras2(cost, v, src);

    nearestpharma(available);

    int chosenPharmacyIndex = chooseNearestPharmacy(available);
    if (chosenPharmacyIndex != -1) {
        printf("\nThe nearest pharmacy is: %s\n", pharma[chosenPharmacyIndex].name);
    } else {
        printf("\nNo pharmacy found.\n");
    }

    int temp;  // Declare temp variable
    int maxDiscountPharmacyIndex = findMaxDiscountPharmacy1(available, temp);
    if (maxDiscountPharmacyIndex != -1) {
        printf("\n SUGGESTIONS :\nThe pharmacy with the highest discount is: %s\n", pharma[maxDiscountPharmacyIndex].name);
    } else {
        printf("\nNo pharmacy found with discount.\n");
    }

    return 0;
}


#include <stdio.h>
#include <limits.h>
#include <stdlib.h>

#define MAX_VERTICES 100
#define MAX_pharma24_7 100
#define INFINITY_COST 9999
#define MAX_NAME_SIZE 15
int global_count3 = 0;

int distance3[MAX_VERTICES];
int path3[MAX_VERTICES];
int visited3[MAX_VERTICES];

typedef struct pharma24_7 {
    int index;
    char name[20];
    int discount;
} PHAR24;

PHAR24 pharma24_7[MAX_pharma24_7];

// Function prototypes
void indexing3(int available[global_count3]);
void dijkstras3(int cost[MAX_VERTICES][MAX_VERTICES], int v, int src);
void loadpharma24_7();
void loadAndGraph3(int cost[MAX_VERTICES][MAX_VERTICES], int v);
void nearestpharma24_7(int available[global_count3]);
void printnearestpharma24_7(int available[global_count3]);
int chooseNearestPharmacy24(int available[global_count3]);
int findMaxDiscountPharmacy(int available[global_count3], int temp);

void indexing3(int available[global_count3]) {
    for (int i = 0; i < global_count3; i++) {
        available[i] = pharma24_7[i].index;
    }
}

void dijkstras3(int cost[MAX_VERTICES][MAX_VERTICES], int v, int src) {
    int j;
    visited3[src] = 1;
    for (j = 0; j < v - 1; j++) {
        int min = INT_MAX;
        int u = 0;
        for (int i = 0; i < v; i++) {
            if (visited3[i] == 0 && distance3[i] < min) {
                min = distance3[i];
                u = i;
            }
        }
        visited3[u] = 1;
        for (int i = 0; i < v; i++) {
            if (visited3[i] == 0 && distance3[i] > cost[u][i] + distance3[u]) {
                distance3[i] = cost[u][i] + distance3[u];
                path3[i] = u;
            }
        }
    }
}

void loadpharma24_7() {
    FILE *file = fopen("pharma24_7.txt", "r");
    if (file == NULL) {
        printf("Error opening file pharma24");
        exit(1);
    }

    while (fscanf(file, "%d %s %d", &pharma24_7[global_count3].index,
           pharma24_7[global_count3].name, &pharma24_7[global_count3].discount) == 3) {
        global_count3++;
    }

    fclose(file);
}

void loadAndGraph3(int cost[MAX_VERTICES][MAX_VERTICES], int v) {
    FILE *file = fopen("pharpath.txt", "r");
    if (file == NULL) {
        printf("Error opening file path3");
        exit(1);
    }

    int x, y, w;
    while (fscanf(file, "%d %d %d", &x, &y, &w) == 3) {
        cost[x][y] = w;
        cost[y][x] = w;
    }

    fclose(file);
}

void nearestpharma24_7(int available[global_count3]) {
    printf("\nNearest pharma24_7 from the source:\n");

    for (int i = 0; i < global_count3; i++) {
        printf("%s is at a distance of %d km provides a discount of %d %%\n", pharma24_7[i].name, distance3[available[i]], pharma24_7[i].discount);
    }
}

void printnearestpharma24_7(int available[global_count3]) {
    printf("\nDistances to all pharma24_7:\n");

    for (int i = 0; i < global_count3; i++) {
        printf("%s is at a distance of %d km provides a discount of %d %%\n", pharma24_7[i].name, distance3[available[i]], pharma24_7[i].discount);
    }
}

int chooseNearestPharmacy24(int available[global_count3]) {
    int minDistance = INT_MAX;

    for (int i = 0; i < global_count3; i++) {
        int currentPharmacy = available[i];
        if (distance3[currentPharmacy] < minDistance) {
            minDistance = distance3[currentPharmacy];
        }
    }

    return minDistance;
}

int findMaxDiscountPharmacy(int available[global_count3], int temp)
//uses selection sort
{
    for (int i = 0; i < global_count3 - 1; i++) {
        int maxIndex = i;
        for (int j = i + 1; j < global_count3; j++) {
            // Compare discounts and update maxIndex for descending order
            if (pharma24_7[j].discount > pharma24_7[maxIndex].discount) {
                maxIndex = j;
            }
        }

        // Swap the pharmacies if needed
        if (maxIndex != i) {
            struct pharma24_7 temp = pharma24_7[i];
            pharma24_7[i] = pharma24_7[maxIndex];
            pharma24_7[maxIndex] = temp;
        }
    }

    // Now the array is sorted in descending order by discount

    // Assuming you want to return the index of the pharmacy with the highest discount
    return 0;
}

void registerPharmacy() {
    FILE *file1 = fopen("pharma24_7.txt", "a");
    FILE *file2 = fopen("pharma.txt", "a");

    if (file1 == NULL || file2 == NULL) {
        printf("Error opening files for registration");
        exit(1);
    }

    printf("\nEnter the name of the new pharmacy: ");
    scanf("%s", pharma24_7[global_count3].name);

    printf("\nEnter the area code of the new pharmacy: ");
    scanf("%d", &pharma24_7[global_count3].index);

    printf("\nEnter discount provided by the pharmacy: ");
    scanf("%d", &pharma24_7[global_count3].discount);

    fprintf(file1, "%d %s %d\n", pharma24_7[global_count3].index, pharma24_7[global_count3].name,
            pharma24_7[global_count3].discount);
    fprintf(file2, "%d %s %d\n", pharma24_7[global_count3].index, pharma24_7[global_count3].name,
            pharma24_7[global_count3].discount);

    fclose(file1);
    fclose(file2);

    global_count3++;
}

void deletePharmacy() {
    int deleteIndex;
    char deletename[MAX_NAME_SIZE];

    printf("\nEnter the area code of the pharmacy to delete: ");
    scanf("%d", &deleteIndex);

    printf("Enter the Pharmacy Name: ");
    scanf("%s", deletename);

    // Search for the pharmacy with the specified area code and name
    int foundIndex = -1;
    for (int i = 0; i < global_count3; i++) {
        if (pharma24_7[i].index == deleteIndex && strcmp(pharma24_7[i].name, deletename) == 0) {
            foundIndex = i;
            break;
        }
    }

    // If the pharmacy is found, delete it
    if (foundIndex != -1) {
        // Shift the remaining elements to overwrite the deleted pharmacy
        for (int i = foundIndex; i < global_count3 - 1; i++) {
            pharma24_7[i] = pharma24_7[i + 1];
        }

        // Decrement the global count to reflect the deletion
        global_count3--;

        printf("Pharmacy with area code %d and name %s has been deleted.\n", deleteIndex, deletename);

        // Rewrite the entire array back to both files after the deletion
        FILE *file1 = fopen("pharma24_7.txt", "w");
        FILE *file2 = fopen("pharma.txt", "w");

        if (file1 == NULL || file2 == NULL) {
            printf("Error opening files for writing");
            exit(1);
        }

        for (int i = 0; i < global_count3; i++) {
            fprintf(file1, "%d %s %d\n", pharma24_7[i].index, pharma24_7[i].name, pharma24_7[i].discount);
            fprintf(file2, "%d %s %d\n", pharma24_7[i].index, pharma24_7[i].name, pharma24_7[i].discount);
        }

        fclose(file1);
        fclose(file2);
    } else {
        printf("Pharmacy with area code %d and name %s not found.\n", deleteIndex, deletename);
    }
}


void pharmareg() {
    char registerOption;
    printf("\nDo you want to register a new pharmacy? (y/n): ");
    scanf(" %c", &registerOption);

    if (registerOption == 'y' || registerOption == 'Y') {
        registerPharmacy();
    }
}


 void pharmacy24(){
    const int v = MAX_VERTICES;
    int cost[MAX_VERTICES][MAX_VERTICES];

    for (int i = 0; i < MAX_VERTICES; i++) {
        for (int j = 0; j < MAX_VERTICES; j++) {
            cost[i][j] = (i == j) ? 0 : INFINITY_COST;
        }
    }

    loadAndGraph3(cost, v);
    loadpharma24_7();

    int available[global_count3];
    indexing3(available);
printf(" CHOSE YOUR AREA CODE:\n 0-Lingrajnagar\n 1-KLE TECH\n 2-Vidyanagar\n 3-KIMS\n 4-Hosur\n 5-Gokul Road\n 6-Shreya Nagar\n 7-Tolankeri\n 8-Chennamma Circle\n 9-HDMC\n 10-Railway Colony\n 11-Unkal\n 12-Navanagar\n 13-Rayapur\n 14-Old Hubli\n");

    int src;
    printf("Enter your location node: ");
    scanf("%d", &src);

    if (src < 0 || src >= v) {
        printf("Invalid source node. Exiting...\n");
        exit(1);
    }

    for (int i = 0; i < v; i++) {
        distance3[i] = cost[src][i];
    }

    for (int i = 0; i < v; i++) {
        path3[i] = src;
    }

    dijkstras3(cost, v, src);

    nearestpharma24_7(available);

    int chosenPharmacyIndex = chooseNearestPharmacy24(available);
    if (chosenPharmacyIndex != -1) {
        printf("\nThe nearest pharmacy is: %s\n", pharma24_7[chosenPharmacyIndex].name);
    } else {
        printf("\nNo pharmacy found.\n");
    }

    int temp;  // Declare temp variable
    int maxDiscountPharmacyIndex = findMaxDiscountPharmacy(available, temp);
    if (maxDiscountPharmacyIndex != -1) {
        printf("\n SUGGESTIONS :\n The pharmacy with the highest discount is: %s\n", pharma24_7[maxDiscountPharmacyIndex].name);
    } else {
        printf("\nNo pharmacy found with discount.\n");
    }



    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_SYMPTOMS 20
#define MAX_DISEASES 20


// Structure for a drug node in AVL Tree
struct DrugNode
{
    char drugName[50];
    char disease[50];  // Disease associated with the drug
    char symptoms[200]; // Symptoms of the disease
    char severity[20];
    struct DrugNode *left;
    struct DrugNode *right;
    int height;
};


// Function to get the height of a node
int heightt(struct DrugNode *node)
{
    if (node == NULL)
        return 0;
    return node->height;
}


// Function to get the maximum of two integers
int max(int a, int b)
{
    return (a > b) ? a : b;
}


// Function to create a new node
struct DrugNode *createNodee(char drugName[], char disease[], char symptoms[], char severity[])
{
    struct DrugNode *node = (struct DrugNode *)malloc(sizeof(struct DrugNode));
    strcpy(node->drugName, drugName);
    strcpy(node->disease, disease);
    strcpy(node->symptoms, symptoms);
    strcpy(node->severity, severity);
    node->left = NULL;
    node->right = NULL;
    node->height = 1; // New node is at height 1
    return node;
}



// Function to perform right rotation
struct DrugNode *rightRotatee(struct DrugNode *y)
{
    struct DrugNode *x = y->left;
    struct DrugNode *T2 = x->right;

    // Perform rotation
    x->right = y;
    y->left = T2;

    // Update heights
    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    return x;
}


// Function to perform left rotation
struct DrugNode *leftRotatee(struct DrugNode *x)
{
    struct DrugNode *y = x->right;
    struct DrugNode *T2 = y->left;

    // Perform rotation
    y->left = x;
    x->right = T2;

    // Update heights
    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    return y;
}


// Function to get the balance factor of a node
int getBalancee(struct DrugNode *node)
{
    if (node == NULL)
        return 0;
    return height(node->left) - height(node->right);

}


// Function to insert a drug into the AVL Tree
struct DrugNode *insertDrug(struct DrugNode *node, char drugName[], char disease[], char symptoms[], char severity[]) {
    // Perform standard BST insertion
    if (node == NULL)
        return createNodee(drugName, disease, symptoms, severity);

    int cmp = strcmp(disease, node->disease);

    if (cmp < 0)

        node->left = insertDrug(node->left, drugName, disease, symptoms, severity);
    else if (cmp > 0)

        node->right = insertDrug(node->right, drugName, disease, symptoms, severity);
    else
     {
        // Duplicate diseases are not allowed
        return node;
    }

    // Update height of the current node
    node->height = 1 + max(height(node->left), height(node->right));

    // Get the balance factor
    int balance = getBalance(node);

    // Perform rotations if needed7
    // Left Left Case
    if (balance > 1 && cmp < 0)
        return rightRotate(node);

    // Right Right Case
    if (balance < -1 && cmp > 0)
        return leftRotate(node);

    // Left Right Case
    if (balance > 1 && cmp > 0)
        {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // Right Left Case
    if (balance < -1 && cmp < 0)
        {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

// Function to search for a drug based on a disease
struct DrugNode *searchDrugForDisease(struct DrugNode *node, char disease[])
{
    if (node == NULL)
        return NULL;


    int cmp = strcmp(disease, node->disease);


    if (cmp < 0)
        return searchDrugForDisease(node->left, disease);

    else if (cmp > 0)
        return searchDrugForDisease(node->right, disease);

    else
        return node;
}

// Function to display the menu and get the choiceee of disease
int getDiseasechoiceee()
{
    int choiceee;

    printf("Choose a disease:\n");

    printf("1. Fever\n");

    printf("2. Hypertension\n");

    printf("3. Cough\n");

    printf("4. Headache\n");
    printf("5. Diabetes\n");


    printf("6. Asthma\n");

    printf("7. Allergies\n");
    printf("8. Arthritis\n");

    printf("9. Osteoporosis\n");

    printf("10. Migraine\n");
    printf("11. Common Cold\n");

    printf("12. Insomnia\n");
    printf("13. Gastroenteritis\n");

    printf("14. Urinary Tract Infection (UTI)\n");
    printf("15. Acid Reflux\n");



    printf("16. Eczema\n");
    printf("17. Anemia\n");

    printf("18. High Cholesterol\n");
    printf("19. Sinusitis\n");

    printf("20. Diarrhea\n");

    printf("Enter your choice: ");
    scanf("%d", &choiceee);

    return choiceee;
}

// Main function for testing the AVL Tree
void medicine()
{
    struct DrugNode *root = NULL;

    FILE *dataFile = fopen("diseases.txt", "r");



    if (dataFile == NULL)
        {
        printf("Error opening the file.\n");
        return 1;
    }

    char drugName[50], disease[50], symptoms[200], severity[20];

    while (fscanf(dataFile, "%[^,],%[^,],%[^,],%[^\n]\n",  disease, symptoms, severity, drugName) != EOF)
        {
        root = insertDrug(root, drugName, disease, symptoms, severity);
    }



    fclose(dataFile);

    int choiceee;
    do
        {
        // Display menu and get the choiceee of disease
        choiceee = getDiseasechoiceee();



        // Search for drugs based on the chosen disease
        char diseases[20][50] = {
            "Fever", "Hypertension", "Cough", "Headache", "Diabetes",

            "Asthma", "Allergies", "Arthritis", "Osteoporosis", "Migraine",

            "Common Cold", "Insomnia", "Gastroenteritis", "Urinary Tract Infection (UTI)",

            "Acid Reflux", "Eczema", "Anemia", "High Cholesterol", "Sinusitis", "Diarrhea"
        };

        if (choiceee >= 1 && choiceee <= 20)
            {
            struct DrugNode *result = searchDrugForDisease(root, diseases[choiceee - 1]);
            if (result != NULL)

            {
                printf("Drug for %s: %s (Severity: %s)\n", result->disease, result->drugName, result->severity);
            } else

            {
                printf("No drug found for %s.\n", diseases[choiceee - 1]);
            }
        } else

        {
            printf("Invalid choiceee. Please try again.\n");
        }

        // Ask if the user wants to continue
        printf("Do you want to search for another disease? (1: Yes, 0: No):\n ");

        scanf("%d", &choiceee);


    } while (choiceee == 1);

    return 0;
}



char symptoms[MAX_SYMPTOMS][100];

char diseases[MAX_DISEASES][100];

char severities[MAX_DISEASES][50];

char medicines[MAX_DISEASES][100];

void readDataFromFile(char *fileName, char data[MAX_DISEASES][100])
{
    FILE *file = fopen(fileName, "r");
    if (file == NULL)
    {
        printf("Error opening file %s.\n", fileName);
        return;
    }

    for (int i = 0; i < MAX_DISEASES; i++)
        {
        if (fgets(data[i], sizeof(data[i]), file) == NULL)
        {
            printf("Error reading data from file.\n");
            break;
        }
        // Remove newline character if present
        char *newline = strchr(data[i], '\n');

        if (newline != NULL) {
            *newline = '\0';
        }
    }

    fclose(file);
}

int rabin_karp(char *text, char *pattern)
{
    int n = strlen(text);

    int m = strlen(pattern);
    int i, j;

    int prime = 101; // A prime number for the hash function
    int pattern_hash = 0;

    int text_hash = 0;
    int h = 1;

    for (i = 0; i < m - 1; i++)
        h = (h * 256) % prime;

    for (i = 0; i < m; i++)

    {
        pattern_hash = (256 * pattern_hash + pattern[i]) % prime;

        text_hash = (256 * text_hash + text[i]) % prime;
    }

    for (i = 0; i <= n - m; i++)
        {
        if (pattern_hash == text_hash)
        {
            for (j = 0; j < m; j++)
            {
                if (text[i + j] != pattern[j])
                    break;
            }
            if (j == m)
                return i;
        }

        if (i < n - m)
            {
            text_hash = (256 * (text_hash - text[i] * h) + text[i + m]) % prime;
            if (text_hash < 0)
                text_hash += prime;
        }
    }

    return -1;
}

void determineDisease(int selectedSymptom)
{
    char selectedSymptomText[100];

    strcpy(selectedSymptomText, symptoms[selectedSymptom - 1]);

    printf("\nSelected Symptom: %s\n", selectedSymptomText);

    int index = -1;
    for (int i = 0; i < MAX_SYMPTOMS; i++)
        {
        if (rabin_karp(selectedSymptomText, symptoms[i]) != -1)
        {
            index = i;
            break;
        }
    }

    if (index != -1)
        {
        printf("Disease: %s\n", diseases[index]);
        printf("Severity: %s\n", severities[index]);
        printf("Medicine: %s\n", medicines[index]);
    } else {
        printf("Disease not found.\n");
    }
}

void disease()
{
    // Read symptoms, diseases, severities, and medicines from the file
    char rawSymptoms[MAX_SYMPTOMS][100];
    readDataFromFile("symptoms.txt", rawSymptoms);


    // Populate diseases, severities, and medicines arrays based on the content of symptoms array
    for (int i = 0; i < MAX_SYMPTOMS; i++)
    {
        sscanf(rawSymptoms[i], "%[^,],%[^,],%[^,],%s", symptoms[i], diseases[i], severities[i], medicines[i]);
    }

    int selectedSymptom;


    // Display the menu
    printf("\nSelect a symptom by entering the corresponding number:\n");
    for (int i = 0; i < MAX_SYMPTOMS; i++)
    {
        printf("%d. %s\n", i + 1, symptoms[i]);
    }


    // Get user input
    printf("\nEnter the number corresponding to the selected symptom: ");
    scanf("%d", &selectedSymptom);


    // Validate user input
    if (selectedSymptom < 1 || selectedSymptom > MAX_SYMPTOMS)
    {
        printf("\nInvalid selection. Please select a number between 1 and %d.\n", MAX_SYMPTOMS);
        return 1;
    }

    // Determine the disease based on the selected symptom
    determineDisease(selectedSymptom);

    return 0;
}





// Define a struct to hold health condition and diet plan
struct HealthData {
    char condition[50];
    char dietPlan[500];
};


// Function to get the diet plan for a given health condition
const char* getDietPlan(struct HealthData healthData[], int size, const char* condition)
{
    for (int i = 0; i < size; ++i)
        {
        if (strcmp(healthData[i].condition, condition) == 0)
        {
            return healthData[i].dietPlan;
        }
    }
    return "Condition not found in the database.";
}
void diet() {
    // Define an array of HealthData
    struct HealthData healthData[] = {
        {"Diabetes", "Include whole grains like brown rice and whole wheat bread. Choose lean protein sources such as chicken, fish, and tofu. Eat plenty of non-starchy vegetables like leafy greens and broccoli. Limit the intake of sugary foods and drinks."},

        {"Hypertension", "Reduce sodium intake by avoiding processed foods and using less salt. Choose lean protein sources and limit red meat consumption. Eat potassium-rich foods like bananas, oranges, and potatoes. Include whole grains and fiber-rich foods in your diet."},
        {"High Cholesterol", "Consume foods rich in omega-3 fatty acids like fatty fish. Choose healthy fats such as avocados and nuts. Include soluble fiber sources like oats and barley. Limit the intake of saturated and trans fats."},

        {"Heart Disease", "Opt for lean protein sources, such as poultry and fish. Consume a variety of fruits and vegetables for antioxidants. Choose whole grains and high-fiber food. Limit salt intake and avoid processed foods."},
        {"Osteoarthritis", "Maintain a healthy weight to reduce stress on joints. Include foods rich in antioxidants such as berries and spinach. Consume omega-3 fatty acids from sources like flaxseeds and walnuts. Consider anti-inflammatory foods like turmeric."},

        {"Celiac Disease", "Avoid gluten-containing grains like wheat, barley, and rye. Choose gluten-free alternatives such as quinoa, rice, and corn. Include nutrient-dense foods like fruits, vegetables, and lean proteins. Check food labels for hidden sources of gluten."},
        {"Irritable Bowel Syndrome", "Identify and avoid trigger foods that worsen symptoms. Consume soluble fiber from oats, bananas, and carrots. Eat smaller, more frequent meals. Stay hydrated and limit caffeine and alcohol intake."},

        {"Lactose Intolerance", "Choose lactose-free or low-lactose dairy products. Opt for lactose-free alternatives like almond or soy milk. Include sources of calcium and vitamin D through non-dairy options. Consider lactase supplements if needed."},
        {"Gastroesophageal Reflux Disease (GERD)", "Avoid acidic and spicy foods that can trigger symptoms. Opt for lean proteins and non-citrus fruits. Eat smaller meals and avoid lying down after eating. Limit caffeine and alcohol consumption."},
        {"Chronic Kidney Disease", "Monitor protein intake and choose high-quality protein sources. Control phosphorus intake by avoiding high-phosphorus foods. Limit sodium intake to help manage blood pressure. Stay hydrated and follow a personalized meal plan."},
        {"Anemia", "Consume iron-rich foods such as lean meats and fortified cereals. Include vitamin C-rich foods to enhance iron absorption. Choose foods rich in folic acid, such as leafy greens and legumes. Consider iron supplements as prescribed."},

        {"Rheumatoid Arthritis", "Include anti-inflammatory foods like fatty fish and olive oil. Consume antioxidant-rich fruits and vegetables. Choose whole grains and limit processed foods. Maintain a healthy weight to reduce joint stress."},
        {"Migraine", "Identify and avoid trigger foods such as chocolate and caffeine. Stay hydrated and maintain regular meal times. Include magnesium-rich foods like nuts and seeds. Consider a low-tyramine diet."},

        {"Asthma", "Consume omega-3 fatty acids from fish and flaxseeds. Include vitamin D-rich foods like fortified dairy products. Opt for antioxidant-rich fruits and vegetables. Limit sulfite-containing foods that may trigger symptoms."},
        {"Psoriasis", "Consume anti-inflammatory foods like fatty fish and berries. Choose whole grains and limit processed foods. Include foods rich in vitamin D, such as fortified dairy. Stay hydrated and maintain a healthy weight."},

        {"Depression", "Include omega-3 fatty acids from fatty fish and flaxseeds. Consume complex carbohydrates from whole grains. Opt for lean proteins like poultry and beans. Stay hydrated and limit caffeine and alcohol."},
        {"Lupus", "Consume anti-inflammatory foods like fatty fish and leafy greens. Include foods rich in antioxidants, such as berries. Choose whole grains and limit processed foods. Stay hydrated and maintain a balanced diet."},

        {"Multiple Sclerosis", "Consume omega-3 fatty acids from fatty fish and flaxseeds. Include vitamin D-rich foods like fortified dairy. Choose antioxidant-rich fruits and vegetables. Consider a balanced diet to support overall health."},
        {"Parkinson's Disease", "Include antioxidant-rich fruits and vegetables. Consume omega-3 fatty acids from fish and nuts. Opt for lean proteins and limit saturated fats. Stay hydrated and maintain a balanced diet."},
        {"Alzheimer's Disease", "Consume omega-3 fatty acids from fatty fish and walnuts. Include antioxidant-rich fruits and vegetables. Choose whole grains and limit refined sugars. Stay hydrated and maintain a balanced diet."}
    };

    // Calculate the size of the array
    int size = sizeof(healthData) / sizeof(struct HealthData);

    // Display available health conditions
    printf("Available Health Conditions:\n");
    for (int i = 0; i < size; ++i) {
        printf("%d. %s\n", i + 1, healthData[i].condition);
    }

    // Get user input for the selected health condition
    int selectedOption;

    printf("\nEnter the number corresponding to the health condition you want a diet plan for: ");
    scanf("%d", &selectedOption);

    // Validate the user input
    if (selectedOption < 1 || selectedOption > size)
    {
        printf("Invalid option. Please select a valid number.\n");
        return 1; // Exit with an error code
    }

    // Get the diet plan for the selected condition
    const char* dietPlan = getDietPlan(healthData, size, healthData[selectedOption - 1].condition);

    // Display the diet plan
    printf("\nDiet Plan for %s:\n%s\n", healthData[selectedOption - 1].condition, dietPlan);

    return 0;
}


void telemedicine()

{
    int choiceeese;
    do{
        printf(" \n1.give medicine based on disease:");

        printf("\n2.predict Disease Based on Symptoms & severity: ");

        printf("\n3.Diet plan for particular disease: ");

        printf("\n4. ENTER choice:");
        scanf("%d",&choiceeese);
        switch(choiceeese)
        {
            case 1:
            {
                medicine();
                break;
            }
            case 2:
            {
                disease();
                break;
            }
            case 3:
            {
                diet();
                break;
            }

            default :
                printf("\nINVALID");
        }

    }

        while(choiceeese != 2);
        return 0;
}


void pharamacistAction() {
    int choi;
    do {
        printf("\n 1.Nearest Pharmacy Open For (9am - 9pm)\n ");
        printf("2.Nearest Pharmacy Open For24*7\n ");
        printf("3.Register as 24*7 Pharmacy\n");
        printf(" 4.De-Register as 24*7 Pharmacy\n");
         printf(" 5.Register as (9am - 9pm) Pharmacy\n");
        printf(" 6.De-Register as (9am - 9pm) Pharmacy\n");
        printf(" 7.Telemedicine \n");
        printf(" 8.Exit \n");
        printf("Enter your choice: ");
        scanf("%d", &choi);
        switch (choi) {
            case 1:{
                pharmacy();}
                break;
            case 2:{
                pharmacy24();
            }
                break;
            case 3:
                pharmareg();
                break;
                 case 4:
                deletePharmacy();
                break;
                case 5:
                pharmareg1();
                break;
                 case 6:
                deletePharmacy1();
                break;
                case 7:
                telemedicine();
                break;
                 case 8:
                    return;
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }

    } while (choi != 0);
}

void loginAction(Graph *doctorGraph) {
    int ch;
    do {
        printf("\nREGISTER AS :\n ");
        printf("\n1. PATIENT\n");
        printf("2. DOCTOR\n");
        printf("3. LAB PERSONNEL\n");
        printf("4. PHARMACIST\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &ch);

        switch (ch) {
            case 1:
                patientAction(doctorGraph);
                break;
            case 2:
                DoctorAction(doctorGraph);
                break;
            case 3:
                LabPersonnalAction();
                break;
            case 4:
                pharamacistAction();
                break;
            case 0:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (ch != 0);
}

#include <stdio.h>
#include <limits.h>
#include <stdlib.h>

#define MAX_VERTICES 100
#define MAX_EDGES 100
#define MAX_HOSPITALS 100
#define INFINITY_COST 9999
#define MAX_NAME_SIZE 15


int global_count = 0;

int distance[MAX_VERTICES];
int path[MAX_VERTICES];
int visited[MAX_VERTICES];

typedef struct hospitals {
    int index;
    char name[20];
    char add[20];
} HOS;
HOS hospitals[MAX_HOSPITALS];

// Function prototypes
void indexing(int available[global_count]);
void dijkstras(int cost[MAX_VERTICES][MAX_VERTICES], int v, int src);
void print(int v);
void loadHospital();
void loadAndGraph(int cost[MAX_VERTICES][MAX_VERTICES], int traffic[MAX_VERTICES][MAX_VERTICES], int v);
void nearestHospital(int available[global_count]);
void printNearestHospital(int available[global_count]);
void ambulance();
void loadGraphForPrim(int* V, int graph[][MAX_VERTICES]);
void prims();
int minKey(int key[], int mstSet[], int V);
void primMST(int V, int graph[MAX_VERTICES][MAX_VERTICES], int src);
void prims();

void indexing(int available[global_count]) {
    for (int i = 0; i < global_count; i++) {
        available[i] = hospitals[i].index;
    }
}

void dijkstras(int cost[MAX_VERTICES][MAX_VERTICES], int v, int src) {
    int j;
    visited[src] = 1;
    for (j = 0; j < v - 1; j++) {
        int min = INT_MAX;
        int u = 0;
        for (int i = 0; i < v; i++) {
            if (visited[i] == 0 && distance[i] < min) {
                min = distance[i];
                u = i;
            }
        }
        visited[u] = 1;
        for (int i = 0; i < v; i++) {
            if (visited[i] == 0 && distance[i] > cost[u][i] + distance[u]) {
                distance[i] = cost[u][i] + distance[u];
                path[i] = u;
            }
        }
    }
    return;
}

void print(int v) {
    printf("\nThe distance array is\n");
    for (int i = 0; i < v; i++) {
        printf("%d ", distance[i]);
    }
    printf("\n");
    printf("The path array is\n");
    for (int i = 0; i < v; i++) {
        printf("%d ", path[i]);
    }
    printf("\n");
    return;
}

void loadHospital() {
    FILE *file = fopen("hos.txt", "r");
    if (file == NULL) {
        printf("Error opening file hos");
        exit(1);
    }
    int x, y, w;
    while (fscanf(file, "%d %s %s", &hospitals[global_count].index, hospitals[global_count].name, hospitals[global_count].add) == 3) {
        global_count++;
    }

    fclose(file);
    return;
}

void loadAndGraph(int cost[MAX_VERTICES][MAX_VERTICES], int traffic[MAX_VERTICES][MAX_VERTICES], int v) {
    FILE *file = fopen("paths.txt", "r");
    if (file == NULL) {
        printf("Error opening file path");
        exit(1);
    }
    int x, y, w, t;
    while (fscanf(file, "%d %d %d %d", &x, &y, &w, &t) == 4) {
        cost[x][y] = w + t;  // Add both weight and traffic
        cost[y][x] = w + t;  // Assume undirected graph
    }

    fclose(file);
    return;
}

void nearestHospital(int available[global_count]) {
    printf("Nearest hospitals from the source:\n");
    for (int i = 0; i < global_count; i++) {
        printf("%s  is at a distance of %d km\n", hospitals[i].name,  distance[available[i]]);
    }
}

void printNearestHospital(int available[global_count]) {
    int minDistance = INT_MAX;
    int nearestHospitalIndex = -1;
    int x;
    int ph_nor;

    for (int i = 0; i < global_count; i++) {
        if (distance[available[i]] < minDistance) {
            minDistance = distance[available[i]];
            nearestHospitalIndex = i;
        }
    }

    if (nearestHospitalIndex != -1) {
        printf("\nNearest hospital: %s %s at the distance of %d\n", hospitals[nearestHospitalIndex].name, hospitals[nearestHospitalIndex].add, minDistance);
        printf("Do You Want To Book Ambulance(1:YES) ");
        scanf("%d", &x);
        if (x == 1) {
            printf("Enter YOUR Phone Nor :");
            scanf("%d",&ph_nor);
            printf("\nYour Ambulance Will be Arriving in %d mins\n\n", minDistance * 2+5);
        } else {
            exit(0);
        }
    }
}

void ambulance() {
    const int v = MAX_VERTICES;
    int cost[MAX_VERTICES][MAX_VERTICES];
    int traffic[MAX_VERTICES][MAX_VERTICES];

    for (int i = 0; i < MAX_VERTICES; i++) {
        for (int j = 0; j < MAX_VERTICES; j++) {
            cost[i][j] = (i == j) ? 0 : INFINITY_COST;
            traffic[i][j] = 0;
        }
    }

    loadAndGraph(cost, traffic, v);
    loadHospital();

    int available[global_count];
    indexing(available);

    int src;
    printf("CHOOSE YOUR LOCATION CODE\n 0-Lingrajnagar\n 1-KLE TECH\n 2-Vidyanagar\n 3-KIMS\n 4-Hosur\n 5-Gokul Road\n 6-Shreya Nagar\n 7-Tolankeri\n 8-Chennamma Circle\n 9-HDMC\n 10-Railway Colony\n 11-Unkal\n 12-Navanagar\n 13-Rayapur\n ");
    printf("Enter your location code\n");
    scanf("%d", &src);

    if (src < 0 || src >= v) {
        printf("Invalid source node. Exiting...\n");
        exit(1);
    }

    for (int i = 0; i < v; i++) {
        distance[i] = cost[src][i];
    }

    for (int i = 0; i < v; i++) {
        path[i] = src;
    }

    dijkstras(cost, v, src);
    nearestHospital(available);
    printNearestHospital(available);
}


#define MAX_LENGTH 256
int KMPSearch(const char *text, const char *pattern) {
    int n = strlen(text);
    int m = strlen(pattern);

    // Step 1: Compute the prefix function π for the pattern P.
    int pi[m];
    pi[0] = 0;
    int k = 0;
    for (int q = 1; q < m; ++q) {
        while (k > 0 && pattern[k] != pattern[q]) {
            k = pi[k - 1];
        }
        if (pattern[k] == pattern[q]) {
            ++k;
        }
        pi[q] = k;
    }

    // Step 2: Set i = 0 (index for text) and j = 0 (index for pattern).
    int i = 0, j = 0;

    // Step 3: While i < n:
    while (i < n) {
        // Step 3a: If P[j] = T[i], increment both i and j.
        if (pattern[j] == text[i]) {
            ++i;
            ++j;
            // Step 3b: If j = m, a match is found at index i - m. Reset j using the prefix function π[j-1].
            if (j == m) {
                return i - j;
            }
        } else {
            // Step 3a: If P[j] != T[i], reset j using the prefix function π[j-1].
            if (j != 0) {
                j = pi[j - 1];
            } else {
                // Step 4: If j = 0, increment i.
                ++i;
            }
        }
    }

    // Step 5: If i = n and no match is found, return -1.
    return -1;
}




int main() {
    Graph doctorGraph;
    initGraph(&doctorGraph);

    createDoctorFromInput(&doctorGraph);

    int cho;
    FILE *fp;
    char username[30];
    char password[30];
    char str[30];
    char str1[30];

    printf("\n\t\t\t\t\t\t WELCOME TO HEALTH CONNECT\n\n");

    do {
        printf("1. LOGIN (Already Existing User)\n");
        printf("2. SIGN IN (Not A USER)\n");
        printf("3. !! AMBULANCE SERVICE !!\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &cho);

        switch (cho)
        {


case 1: {
                fp = fopen("password.txt", "r");

                if (fp == NULL) {
                    printf("ERROR: Could not open file password\n");
                    exit(1);
                }

                printf("Enter Username\n");
                scanf("%s", username);
                printf("Enter your password\n");
                scanf("%s", password);

                int access = 0;
                while (fgets(str, sizeof(str), fp) != NULL) {
                    str[strcspn(str, "\n")] = '\0'; // Remove the newline character read by fgets
                    char *savedUsername = strtok(str, " \t");
                    char *savedPassword = strtok(NULL, " \t");

                    if (savedUsername != NULL && savedPassword != NULL) {
                        // Use KMP search to check for username and password match
                        int result = KMPSearch(savedUsername, username);
                        if (result != -1 && strcmp(savedPassword, password) == 0) {
                            printf("Hello %s! You are logged in and WELCOME TO HEALTH CONNECT\n", username);
                            access = 1;
                                            loginAction(&doctorGraph);


                            break;
                        }
                    }
                }

                if (access == 0) {
                    printf("YOUR USERNAME OR PASSWORD IS INCORRECT\n");
                }

                fclose(fp);
                break;
            }




            case 2:
                fp = fopen("password.txt", "a");

                if (fp == NULL ) {
                    printf("Error password file\n");
                    return 1; // Exit the program with an error code
                }

                printf("Enter your username\n");
                scanf("%s", username);
                fprintf(fp, "\n%s", username);
                printf("Enter 3-character password\n");
                scanf("%s", password);
                fprintf(fp, "\t%s", password);
                printf("Hey %s, your account has been created. You can log in now.\n", username);
                fclose(fp);
                 break;
            case 3:
               ambulance();
                break;
            case 4:
                printf("\nExiting...\n");
                exit(0);
                break;
            default:
                printf("\nInvalid choice. Please try again.\n");
        }
    } while (cho != 4);

return 0;
}
