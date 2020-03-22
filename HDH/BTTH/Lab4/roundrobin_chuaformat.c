/*
Mot so tham so va ham duoc cai them de phuc vu debug, khong lien quan toi ket qua output chuong trinh
*/

#include <stdio.h>
#include <string.h>

int number_of_processes; //number of process
int quantum_time;        //quantum time

int number_of_steps = 0;

#define inputFileName "input.txt" //%s
#define outputFileName "output.txt"

typedef struct processStruct
{
    int Name;
    int BurstTime;
    int StartTime;
    int StopTime;
    int WaitTime;
    int RespondTime;
    int TurnAroundTime;
    int RemainingTime;
} processStruct;

int SumWaitingTime = 0;
int SumTurnAroundTime = 0;
float AVGWaitingTime;
float AVGTurnArroundTime;
int SumBurstTime = 0;
int SumRemainingTime = 0;

//Load resouces
void LoadResouces(processStruct processes[])
{
    FILE *input_file;

    input_file = fopen(inputFileName, "rt");
    fscanf(input_file, "%d", &number_of_processes); //get number of process
    fscanf(input_file, "%d", &quantum_time);        //get quantum time

    for (int i = 1; i <= number_of_processes; i++) //get name and burst time of all process
    {
        fscanf(input_file, "%d", &processes[i - 1].Name);
        fscanf(input_file, "%d", &processes[i - 1].BurstTime);
        processes[i - 1].RemainingTime = processes[i - 1].BurstTime;
    }

    fclose(input_file);
}

//Debug
void OutputDebug(processStruct processes[])
{
    printf("%d%6d", number_of_processes, quantum_time);
    printf("\n");
    for (int i = 0; i < number_of_processes; i++)
    {
        printf("%d", processes[i].Name);
        printf("%6d", processes[i].BurstTime);
        printf("%6d\n", processes[i].RemainingTime);
    }
    printf("Sum BurstTime:%d\n", SumBurstTime);
    printf("Number of Steps:%d\n", number_of_steps);
}

int main()
{
    processStruct processes[100];
    LoadResouces(processes);

    int SumConsumedTime = 0;

    //Calculate sum of burst time
    for (int i = 0; i < number_of_processes; i++)
    {
        SumBurstTime += processes[i].BurstTime;
    }
    SumRemainingTime = SumBurstTime;

    //Calculate number of steps
    //OutputDebug(processes);

    //   printf("-----------\n");
    FILE *output_file = fopen(outputFileName, "wt");
    while (SumRemainingTime > 0)
    {
        for (int i = 0; i < number_of_processes; i++)
        {
            if (processes[i].RemainingTime == 0)
            {
                continue;
            }
            if (processes[i].RemainingTime > quantum_time)
            {
                fprintf(output_file,"%d", processes[i].Name); //Xuat ten
                fprintf(output_file,"%6d", SumConsumedTime);  //Xuat StartTime cua buoc hien tai
                SumConsumedTime += quantum_time;  //Tinh toan tong thoi gian da ton
                processes[i].RemainingTime -= quantum_time;
                number_of_steps += 1;
                SumRemainingTime -= quantum_time;
                fprintf(output_file,"%6d\n", SumConsumedTime); //Xuat thoi gian ket thuc cua tien trinh hien tai
                //printf("%6d", processes[i].RemainingTime); //Xuat so thoi gian con lai cua 1 tien trinh
                // printf("%6d\n", SumRemainingTime); //Xuat tong thoi gian con lai cua tat ca tien trinh
                continue;
            }
            if (processes[i].RemainingTime < quantum_time || processes[i].RemainingTime == quantum_time)
            {
                fprintf(output_file,"%d", processes[i].Name);              //Xuat ten
                fprintf(output_file,"%6d", SumConsumedTime);               //Xuat StartTime cua buoc hien tai
                SumConsumedTime += processes[i].RemainingTime; //Tinh toan tong thoi gian da ton
                SumRemainingTime -= processes[i].RemainingTime;
                processes[i].TurnAroundTime = SumConsumedTime; //Tinh thoi gian hoan thanh cua tien trinh hien tai
                processes[i].RemainingTime = 0;
                number_of_steps += 1;
                fprintf(output_file,"%6d\n", SumConsumedTime); //Xuat thoi gian ket thuc cua tien trinh hien tai
                //printf("%6d", processes[i].RemainingTime); //Xuat thoi gian con lai cua tien trinh
                //printf("%6d\n", SumRemainingTime); //Xuat tong thoi gian con lai
                continue;
            }
        }
    }
    // printf("\n");
    for (int i = 0; i < number_of_processes; i++)
    {
        //printf("%d", processes[i].Name);
        //printf("%6d", processes[i].TurnAroundTime);
        processes[i].WaitTime = processes[i].TurnAroundTime - processes[i].BurstTime;
        //printf("%6d\n", processes[i].WaitTime);
    }

    for (int i = 0; i < number_of_processes; i++)
    {
        SumTurnAroundTime += processes[i].TurnAroundTime;
        SumWaitingTime = processes[i].WaitTime;
    }

    fprintf(output_file,"%0.2f", 1.0 * SumTurnAroundTime / number_of_processes);
    fprintf(output_file,"\n%0.2f", 1.0 * SumWaitingTime / number_of_processes);
    //printf("%d\n", number_of_steps);
    fclose(output_file);
    return 0;
}
