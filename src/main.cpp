#include "integer.h"
#include <iostream>
#include <iterator>
#include <list>
#include <numeric>
#include <set>
#include <sstream>
#include <vector>
#include <algorithm>

enum argv_pos {
    ARGV_NUMBER = 1
};

template<typename T>
std::ostream& operator<<(std::ostream& out, const std::list<T>& list) {
    for (const auto el : list) {
        out << el << ' ';
    }

    return out;
}

template<typename T>
std::ostream& operator<<(std::ostream& out, const std::vector<T>& vec) {
    for (const auto el : vec) {
        out << el << ' ';
    }

    return out;
}

template<typename T, typename R>
std::ostream& operator<<(std::ostream& out, const std::pair<T, R>& p) {
    out << "{ " << p.first << ", " << p.second << " }";

    return out;
}


int main(int argc, char **argv) {
    int vector_size = 0;

    if (argc < 2) {
        std::cerr << "No arguments given." << std::endl;
        return 1;
    }

    int num = 1;
    int denom = 5;

    // Создать вектор v1 размером от 500 до 1000 элементов, число элементов не известно до
    // запуска программы. Элементами вектора являются экземпляры класса из Л.Р. №2 имеющие
    // произвольные(случайные) значения. В случае необходимости этот класс должен быть доработан
    // для возможности решать поставленные в этой ЛР задачи.

    std::istringstream num_stream(argv[ARGV_NUMBER]);
    num_stream >> vector_size;

    std::vector<Integer> vec1(vector_size);
    for (int i = 0; i < vec1.size(); i++) {
        vec1[i] = Integer(num + i);
    }

    std::cout << "vec1: after construction" << vec1 << std::endl;

    int b = vector_size - 200;
    int e = vector_size;

    // Создать вектор v2, поместив в него последние 200 элементов вектора v1. Рассмотрите
    // решение для произвольных b и e, которые задают позиции первого и последнего копируемых
    // элементов.

    std::vector<Integer> vec2(vec1.begin() + b, vec1.end());

    std::cout << "vec2: after contruction" << vec2 << std::endl;

    int list_el = 20;

    std::sort(vec1.begin(), vec1.end());
    std::sort(vec2.begin(), vec2.end());

    // Сформировать список list1, поместив в него первые n (от 20 до 50) наибольших элементов
    // вектора v1 (указанные элементы должны быть отсортированы до помещения их в список).

    std::list<Integer> list1(vec1.end() - list_el, vec1.end());

    // Сформировать список list2, поместив в него последние n (от 20 до 50) наименьших элементов
    // вектора v2, порядок элементов не важен.

    std::list<Integer> list2(vec2.begin(), vec2.begin() + list_el);

    std::cout << "list1 after construction: " << list1 << std::endl;
    std::cout << "list2 after construction: " << list2 << std::endl;

    // Удалить из векторов v1 и v2 перемещенные элементы. Скорректируйте размеры векторов
    // после удаления из них элементов.

    std::cout << "vec1 before erasing: " << vec1 << std::endl;
    std::cout << "vec2 before erasing: " << vec2 << std::endl;

    vec1.erase(vec1.end() - list_el, vec1.end());
    vec2.erase(vec2.begin(), vec2.begin() + list_el);

    std::cout << "vec1 after erasing: " << vec1 << std::endl;
    std::cout << "vec2 after erasing: " << vec2 << std::endl;

    vec1.shrink_to_fit();
    vec2.shrink_to_fit();

    // Для списка list1 найти элемент со средним значением. Перегруппировать элементы списка
    // так, чтобы в начале оказались все элементы, большие среднего значения.

    std::cout << "list1 before moving: " << list1 << std::endl;

    Integer avg = std::reduce(list1.begin(), list1.end(), Integer(0),
        [](const Integer& init, const Integer& operand) {
            return init + operand;
        }) / list1.size();

    std::cout << "Average: " << avg << std::endl;

    auto pivot_iter = std::find_if(list1.begin(), list1.end(),
        [&avg](const Integer& i) {
            return i > avg;
        });

    list1.splice(list1.begin(), list1, pivot_iter, list1.end());

    std::cout << "list1 after moving: " << list1 << std::endl;

    // Удалите из списка list2 все нечётные элементы (или используйте другой критерий,
    // который однозначно делит экземпляры вашего класса на два непересекающихся множества).

    std::cout << "list2 before erasing odd elements: " << list2 << std::endl;

    auto list2_new_end = std::remove_if(list2.begin(), list2.end(), [](const Integer& i) { return i % 2 == 0; });
    list2.erase(list2_new_end, list2.end());

    std::cout << "list2 after erasing odd elements: " << list2 << std::endl;

    // Создайте вектор v3 из элементов, которые присутствуют и в векторе v1 и в векторе v2.
    std::vector<Integer> vec3;
    std::set_intersection(vec1.begin(), vec1.end(), vec2.begin(), vec2.end(), std::back_inserter(vec3));

    std::cout << "vec3 after construction: " << vec3 << std::endl;

    // Для списков list1 и list2 из списка с большим числом элементов удалите первые n так,
    // чтобы оба списка имели бы одинаковый размер. Сформируйте из них список list3, который
    // будет хранить пары <первый элемент списка list1, первый элемент списка list2>,
    // <второй элемент списка list1, второй элемент списка list2>  и т. д.

    auto tmp_iter = list1.begin();
    std::advance(tmp_iter, list1.size() - list2.size());

    list1.erase(list1.begin(), tmp_iter);

    std::list<std::pair<Integer, Integer>> list3;
    std::transform(list1.begin(), list1.end(), list2.begin(), std::back_inserter(list3),
        [](const Integer& i1, const Integer& i2) {
            return std::pair<Integer, Integer>{ i1, i2 };
        });

    std::cout << "list3 after construction: " << list3 << std::endl;

    // Решите предыдущую задачу для векторов v1 и v2 без предварительного приведения векторов
    // к одному размеру. Пар с пустыми значениями быть не должно.

    std::vector<std::pair<Integer, Integer>> vec4;
    std::transform(vec2.begin(), vec2.end(), vec1.begin(), std::back_inserter(vec4),
        [](const Integer& i1, const Integer& i2) {
            return std::pair<Integer, Integer>{ i1, i2 };
        });

    std::cout << "vec4 after construction: " << vec4 << std::endl;

    return 0;
}