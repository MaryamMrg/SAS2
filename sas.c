#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct
{
    int day;
    int month;
    int year;
} Date;

typedef struct
{
    char title[50];
    char desc[100];
    Date duedate;
    int priority;
    int statut;
} Task;

Task tasks[100];
int nTasks = 0;

void menu()
{
    printf("*\n");
    printf("***                 TASK MANAGEMENT                ***\n");
    printf("*\n");
    printf("***             1: ADD A TASK                               ***\n");
    printf("***             2: VIEW THE LIST OF TASKS                   ***\n");
    printf("***             3: MODIFY A TASK                            ***\n");
    printf("***             4: DELETE A TASK                            ***\n");
    printf("***             5: ORGANIZE THE TASKS                       ***\n");
    printf("***             6: FILTER THE TASKS                         ***\n");
    printf("***             7: QUIT THE APPLICATION                     ***\n");
    
    printf("*\n");
}

void inputUser(int index)
{
    printf("Title of the task : ");
    scanf(" %[^\n]", tasks[index].title);
    printf("Description of the task : ");
    scanf(" %[^\n]", tasks[index].desc);
    printf("duedate (JJ/MM/AAAA) : ");
    scanf("%d/%d/%d", &tasks[index].duedate.day, &tasks[index].duedate.month, &tasks[index].duedate.year);
    printf("Priorite (1: High 2: low) : ");
    scanf("%d", &tasks[index].priority);
    printf("Statut (1: complete, 2: incomplete) : ");
    scanf("%d", &tasks[nTasks].statut);
}

void addtask()
{
    if (nTasks == 100)
    {
        printf("the list of tasks full.\n");
        return;
    }
    else
    {
        inputUser(nTasks);
        nTasks++;
        printf("Task added succefully.\n");
    }
}

void view(int i)
{
    printf("Taske %d\n", i + 1);
    printf("title : %s\n", tasks[i].title);
    printf("Description : %s\n", tasks[i].desc);
    printf("Due date : %d/%d/%d\n", tasks[i].duedate.day, tasks[i].duedate.month, tasks[i].duedate.year);
    switch (tasks[i].priority)
    {
    case 1:
        printf("Priority : High\n");
        break;
    case 2:
        printf("Priority : low\n");
        break;
    
    default:
        printf("Priority : not recognized\n");
    }
    printf("Statut : %s\n", tasks[i].statut == 1 ? "complete" : "incomplete");
    printf("\n--------------------------------------------------------------\n");
}

void viewtasks()
{
    if (nTasks <= 0)
    {
        printf("List of tasks emppty!!!\n");
        return;
    }
    else
    {
        printf("--------------------------------------------------------------\n");
        printf("|                      List of tasks                     |\n");
        printf("--------------------------------------------------------------\n");
        for (int i = 0; i < nTasks; i++)
        {
            view(i);
        }
    }
}

void echange(int i, int j)
{
    Task temp = tasks[j];
    tasks[j] = tasks[i];
    tasks[i] = temp;
}

void modifytask()
{
    int index;
    printf("Enter the id of the task: ");
    scanf("%d", &index);
    if (index < 1 || index > nTasks)
    {
        printf("id invalide.\n");
        return;
    }
    else
    {
        inputUser(index - 1);
        printf("Task modified succefully.\n");
    }
}

void deletetask()
{
    int index;
    printf("Enter id of the task: ");
    scanf("%d", &index);
    if (index < 1 || index > nTasks)
    {
        printf("id Invalide.\n");
        return;
    }
    else
    {
        for (int i = index - 1; i < nTasks - 1; i++)
        {
            strcpy(tasks[i].title, tasks[i + 1].title);
            strcpy(tasks[i].desc, tasks[i + 1].desc);
            tasks[i].duedate = tasks[i + 1].duedate;
            tasks[i].priority = tasks[i + 1].priority;
            tasks[i].statut = tasks[i + 1].statut;
        }
        nTasks--;
        printf("Task deleted succefully.\n");
    }
}

void organizetasks()
{
    int ordre;
    if (nTasks <= 0)
    {
        printf("List of tasks empty!!!\n");
        return;
    }
    else
    {
        printf("Choose the order (1: ascending, 2: descending): ");
        scanf("%d", &ordre);
        for (int i = 0; i < nTasks - 1; i++)
        {
            for (int j = i + 1; j < nTasks; j++)
            {
                if (ordre == 1)
                {
                    if (tasks[i].duedate.year== tasks[j].duedate.year && tasks[i].duedate.month > tasks[j].duedate.month ||
                        (tasks[i].duedate.year == tasks[j].duedate.year && tasks[i].duedate.month )|| (tasks[j].duedate.month && tasks[i].duedate.day > tasks[j].duedate.day))
                    {
                        echange(i, j);
                    }
                    printf("Task ordred ascending .\n");
                }
                else
                {
                    if (tasks[i].duedate.year < tasks[j].duedate.year ||
                        (tasks[i].duedate.year== tasks[j].duedate.year&&tasks[i].duedate.month < tasks[j].duedate.month) ||
                        (tasks[i].duedate.year == tasks[j].duedate.year && tasks[i].duedate.month == tasks[j].duedate.month && tasks[i].duedate.day < tasks[j].duedate.day))
                    {
                        echange(i, j);
                    }
                    printf("Task ordred descending.\n");
                }
            }
        }
        viewtasks();
    }
}

void filtertasks()
{
    int filter, priority, statut;
    Date date;
    printf("Choose filter (1: Priority, 2: Statut) : ");
    scanf("%d", &filter);
    switch (filter)
    {
    case 1:
        printf("Enter the Priority (1: high, 2: low) : ");
        scanf("%d", &priority);
        printf("--------------------------------------------------------------\n");
        printf("|            List of tasks filtered by priority            |\n");
        printf("--------------------------------------------------------------\n");
        for (int i = 0; i < nTasks; i++)
        {
            if (tasks[i].priority == priority)
            {
                view(i);
            }
        }
        break;

    case 2:
        printf("Statut (1: complete, 2: incomplete) : ");
        scanf("%d", &statut);
        printf("--------------------------------------------------------------\n");
        printf("|            List of tasks filtered by statut            |\n");
        printf("--------------------------------------------------------------\n");
        for (int i = 0; i < nTasks; i++)
        {
            if (tasks[i].statut == statut)
            {
                view(i);
            }
        }break;
    default:
        printf("choice invalid!!");
        break;
    }
}


int main()
{
    int choice;
    printf("*\n");
    printf("***              Realise par: Maryam EL OUADAA             ***\n");
    printf("***                        ENAA BM                       ***\n");
    do
    {
        menu();
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            addtask();
            break;
        case 2:
            viewtasks();
            break;
        case 3:
            modifytask();
            break;
        case 4:
           deletetask();
            break;
        case 5:
            organizetasks();
            break;
        case 6:
            filtertasks();
            break;
        case 7:
            printf("merci by by!");
            return 0;
        
        default:
            printf("Choice invalid\n");
            break;
        }
    } while (choice != 8);
    return 0;
}