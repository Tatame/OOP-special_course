#include <iostream>
#include <vector>
#include "Container.h"
#include "AbstractClass.h"

int main(int argc, char **argv){
    auto task_container = new Container<Task>();
    auto string_container = new Container<std::string>;
    task_container->push_back(new TaskMinus(8, 4, "-"));
    task_container->push_back(new TaskPlus(8, 4, "+"));
    task_container->push_back(new TaskMultiply(10, 10, "*"));
    task_container->push_back(new TaskAddAnotherTask(new TaskResTaskCountInContainer(task_container), task_container));
    task_container->push_back(new TaskDivide(1, 3, "/"));
    task_container->push_back(new TaskMinus(4, 8, "-"));
    task_container->push_back(new TaskDivide(0, 8, "/"));
    task_container->push_back(new TaskResTaskCountInContainer(task_container));
    task_container->push_back(new TaskObjCountInContainer(task_container));
    task_container->push_back(new TaskObjCount());
    task_container->push_back(new TaskAddAnotherTask(new TaskObjCountInContainer(task_container), task_container));
    task_container->push_back(new TaskAddAnotherTask(new TaskObjCount, task_container));
    task_container->push_back(new TaskAddAnotherTask(new TaskClearContainer(task_container), task_container));

    std::cout << "Objects in program : " << Object::get_number_of_copies() << std::endl;

    while (!task_container->is_empty()){
        auto tmp = task_container->get_first_element();
        task_container->pop_front();
        tmp->execute();
        string_container->push_back(new std::string(tmp->toString()));
        delete tmp;
    }

    for (auto x : *string_container){
        std::cout << *x << std::endl;
    }

    std::cout << "Objects in program : " << Object::get_number_of_copies() << std::endl;

    delete task_container;
    delete string_container;
    return 0;
}
