#include <assert.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <uv.h>

void on_read(uv_fs_t *req);

uv_fs_t open_req;
uv_fs_t read_req;
uv_fs_t write_req;

static char buffer[1024];

static uv_buf_t iov;

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

void on_write(uv_fs_t *req)
{
    if (req->result < 0)
    {
        fprintf(stderr, "Write error: %s\n", uv_strerror((int)req->result));
    }
    else
    {
        uv_fs_read(uv_default_loop(), &read_req, open_req.result, &iov, 1, -1, on_read);
    }
}

void on_read(uv_fs_t *req)
{
    if (req->result < 0)
    {
        fprintf(stderr, "Read error: %s\n", uv_strerror(req->result));
    }
    else if (req->result == 0)
    {
        uv_fs_t close_req;
        // synchronous
        uv_fs_close(uv_default_loop(), &close_req, open_req.result, NULL);
    }
    else if (req->result > 0)
    {
        iov.len = req->result;
        uv_fs_write(uv_default_loop(), &write_req, 1, &iov, 1, -1, on_write);
    }
}

void on_open(uv_fs_t *req)
{
    // The request passed to the callback is the same as the one the call setup
    // function was passed.
    assert(req == &open_req);
    if (req->result >= 0)
    {
        iov = uv_buf_init(buffer, sizeof(buffer));
        uv_fs_read(uv_default_loop(), &read_req, req->result,
                   &iov, 1, -1, on_read);
    }
    else
    {
        fprintf(stderr, "error opening file: %s\n", uv_strerror((int)req->result));
    }
}

int main(int argc, char **argv)
{
    // The path of the file to be opened is supplied via the cli arguments to running the executable
    // The path is captured in argv[1]
    uv_fs_open(uv_default_loop(), &open_req, argv[1], O_RDONLY, 0, on_open);
    uv_run(uv_default_loop(), UV_RUN_DEFAULT);

    uv_fs_req_cleanup(&open_req);
    uv_fs_req_cleanup(&read_req);
    uv_fs_req_cleanup(&write_req);
    return 0;
}
