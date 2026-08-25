#include <stdio.h>
#include <string.h>

struct address
{
    char city[20];
    char street[20];
};

struct person
{
    char name[20];
    int age;
    float height;
    struct address home_address;
};

void print_person(struct person person);

int main(void)
{
    struct person student = {
        "张三",
        20,
        1.75f,
        {"北京", "长安街"}
    };

    struct person *person_pointer = &student;

    person_pointer->age = 21;
    strcpy(person_pointer->home_address.city, "上海");

    print_person(student);

    return 0;
}

void print_person(struct person person)
{
    printf("名字：%s\n", person.name);
    printf("年龄：%d\n", person.age);
    printf("身高：%.2f\n", person.height);
    printf("城市：%s\n", person.home_address.city);
    printf("街道：%s\n", person.home_address.street);
}
