#include <iostream>
#include <cstdarg>

#ifndef NULL
#define NULL 0
#endif

using namespace std;

class NODE
{
private:
    int power;
    int coefficient;
    NODE *next_node;

public:
    NODE()
    {
        this->power = 0;
        this->coefficient = 0;
        this->next_node = NULL;
    }

    NODE(int power_setter, int coefficient_setter)
    {
        this->power = power_setter;
        this->coefficient = coefficient_setter;
        this->next_node = NULL;
    }

    void set_power(int setter_val) {
        this->power = setter_val;
    }

    void set_coefficient(int setter_val) {
        this->coefficient = setter_val;
    }

    void set_next(NODE *setter_node) {
        this->next_node = setter_node;
    }

    int get_power() { return this->power; }

    int get_coefficient() { return this->coefficient; }

    NODE* get_next() { return this->next_node; }


    // considering implementing this later

    // NODE& operator++()
    // {
    //     NODE* overload_temp;
    //     overload_temp = this->get_next();
    //     this;

    //     return *this;
    // }

};

class SINGLY_LINKED_LIST
{
    private:
        NODE *head;
        NODE *tail;

    public:
        SINGLY_LINKED_LIST()
        {
            this->head = new NODE();
            this->tail = new NODE();

            this->head->set_next(NULL);
            this->tail->set_next(NULL);
        }

        bool is_empty() { return this->head == NULL; }

        void insert_as_first(NODE* to_insert)
        {
            if (this->is_empty())
            {
                this->head->set_next(to_insert);
                this->tail->set_next(to_insert);
                to_insert->set_next(NULL);
            }
            else
            {
                to_insert->set_next(this->head->get_next());
                this->head->set_next(to_insert);
            }
        }

        void insert_as_last(NODE* to_insert)
        {
            if (this->is_empty())
            {
                this->insert_as_first(to_insert); // no need to re-write
            }
            else
            {
                to_insert->set_next(NULL);
                this->tail->get_next()->set_next(to_insert);
                this->tail->set_next(to_insert);
            }
        }

        void insert_after(NODE* after_this_node, NODE* to_insert)
        {
            if (this->is_empty() || after_this_node == NULL) cout << "Incorrect use of 'insert_after()'. " << endl;
            else
            {
                if (tail->get_next() == after_this_node)
                {
                    tail->get_next()->set_next(to_insert);
                    tail->set_next(to_insert);
                    to_insert->set_next(NULL);
                }
                else
                {
                    NODE *list_iterator = this->head->get_next();

                    while (list_iterator != NULL && list_iterator != after_this_node)
                    {
                        list_iterator = list_iterator->get_next();
                    }

                    if (list_iterator != NULL)
                    {
                        to_insert->set_next(list_iterator->get_next());
                        list_iterator->set_next(to_insert);
                    }
                    else cout << "Node relative to which 'insert_after()' was called not found within list. " << endl;
                }
            }
        }

        void insert_before(NODE* before_this_node, NODE* to_insert)
        {
            if (this->is_empty() || before_this_node == NULL) cout << "Incorrect use of 'insert_before()'. " << endl;
            else
            {
                if (head->get_next() == before_this_node)
                {
                    to_insert->set_next(head->get_next());
                    head->set_next(to_insert);
                }
                else
                {
                    NODE *list_iterator = this->head->get_next();

                    while (list_iterator->get_next() != NULL && list_iterator->get_next() != before_this_node)
                    {
                        list_iterator = list_iterator->get_next();
                    }

                    if (list_iterator->get_next() != NULL)
                    {
                        to_insert->set_next(list_iterator->get_next());
                        list_iterator->set_next(to_insert);
                    }
                    else cout << "Node relative to which 'insert_before()' was called not found within list. " << endl;
                }
            }
        }

        NODE* get_first_asptr() { return this->head->get_next(); }

        NODE* remove_first() {
            if (this->is_empty()) return NULL;
            else
            {
                NODE *fetched_first = this->head->get_next();

                this->head->set_next(this->head->get_next()->get_next());
                if (this->head->get_next() == NULL) this->tail->set_next(NULL);

                fetched_first->set_next(NULL);

                return fetched_first;
            }
        }

};

class POLYNOMIAL
{
    private:
        SINGLY_LINKED_LIST *representation;
        int degree;
        bool is_zero_polynomial;

    public:

        static int overloaded;

        POLYNOMIAL()
        {
            this->representation = new SINGLY_LINKED_LIST();
            this->degree = 0;
            this->is_zero_polynomial = true;
        }

        POLYNOMIAL(int degree_setter, ...)
        {
            va_list coefficients;
            va_start (coefficients, degree_setter);

            this->representation = new SINGLY_LINKED_LIST();

            if (degree_setter == 0)
            {
                this->degree = 0;
                int retrieve_constant = va_arg(coefficients, int);

                switch (retrieve_constant)
                {
                    case 0:
                        this->is_zero_polynomial = true;
                        break;

                    default:
                        this->is_zero_polynomial = false;
                        this->representation->insert_as_first(new NODE(0, retrieve_constant));
                }
            }
            else
            {
                this->degree = degree_setter;

                for (int i = 0; i <= degree_setter; ++i)
                {
                    this->representation->insert_as_first(new NODE(i, va_arg(coefficients, int)));
                }
            }

            va_end(coefficients);
        }

        ~POLYNOMIAL() { delete this->representation; } // to-do: implement list destructor, if needed

        SINGLY_LINKED_LIST* fetch_representation_addr() { return this->representation; }

        bool is_zero() { return this->is_zero_polynomial; }

        int get_degree() { return this->degree; }

        bool operator==(POLYNOMIAL right_argument)
        {
            if (this->representation != right_argument.representation) return false;
            return true;
        }

        POLYNOMIAL& operator=(POLYNOMIAL right_argument)
        {
            if (right_argument.representation == this->representation)
            {
                return *this;
            }
            else
            {
                delete this->representation;
                this->representation = new SINGLY_LINKED_LIST();

                if (right_argument.is_zero_polynomial)
                {
                    this->degree = 0;
                    this->is_zero_polynomial = true;
                }
                else
                {
                    this->degree = right_argument.degree;
                    this->is_zero_polynomial = false;

                    for (int i = 0; i <= this->degree; ++i)
                    {
                        this->representation->insert_as_first(right_argument.representation->remove_first());
                    }
                }

                return *this;
            }
        }
};

ostream& operator<<(ostream& OUT_STREAM, POLYNOMIAL& to_print)
{
    OUT_STREAM << "( ";

    if (to_print.is_zero())
    {
        OUT_STREAM << "0 )";
    }
    else
    {
        NODE* list_iterator = to_print.fetch_representation_addr()->get_first_asptr();
        SINGLY_LINKED_LIST *reversed_list = new SINGLY_LINKED_LIST();

        while (list_iterator != NULL)
        {
            reversed_list->insert_as_first(list_iterator);
            list_iterator = list_iterator->get_next();
        }

        if (!reversed_list->is_empty())
        {
            list_iterator = reversed_list->get_first_asptr();

            while (list_iterator->get_next() != NULL)
            {
                OUT_STREAM << list_iterator->get_coefficient() << ", ";
                list_iterator = list_iterator->get_next();
            }

            OUT_STREAM << list_iterator->get_next()->get_coefficient() << " )";
        }

        delete reversed_list;
    }

    return OUT_STREAM;
}

istream& operator>>(istream& IN_STREAM, POLYNOMIAL& to_save_read) {
    return IN_STREAM;
}

/*
int main()
{
    POLYNOMIAL* A = new POLYNOMIAL();

    cout << "Compiled!" << endl;

    delete A;

    return 0;
}
*/
