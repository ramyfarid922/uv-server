#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <uv.h>

int64_t counter = 0;

void runCPlayground()
{
    /* Definning a new type from struct */
    struct Employee
    {
        int nr;
        int years;
        char name[20];
        double salary;
    };
    typedef struct Employee Employee;

    /* Variable definition/declaration */
    Employee e1 = {1, 2, "Ramy", 1200.00};
    Employee e2;

    /* Fill some data about employees in another way */
    e2.nr = 2;
    e2.years = 3;
    strncpy(e2.name, "Thomas", 20);
    e2.salary = 1300.50;

    printf("Employee 1 is %s and gets a monthly salary of %.2f\n", e1.name, e1.salary);
    printf("Employee 2 is %s and gets a monthly salary of %.2f\n", e2.name, e2.salary);

    struct Employee e3 = {3, 5, "Bill", 1900.50};
}

void wait_for_a_while(uv_idle_t *handle)
{
    counter++;

    if (counter >= 10e6)
        uv_idle_stop(handle);
}

int main(int argc, char **argv)
{
    uv_idle_t idler;

    uv_idle_init(uv_default_loop(), &idler);
    uv_idle_start(&idler, wait_for_a_while);

    printf("Idling...\n");
    uv_run(uv_default_loop(), UV_RUN_DEFAULT);

    uv_loop_close(uv_default_loop());
    return 0;
}