#ifndef ORM_TABLECREATOR_HPP
#define ORM_TABLECREATOR_HPP

#include <string>

namespace orm
{
    class TableCreator
    {
        public:

            /**
             * \brief create a autoField culumn
             * \param colunm_name the column name
             */
            virtual std::string autoField(const std::string& colunm_name) const = 0;

            /**
             * \brief create a booleanField culumn
             * \param colunm_name the column name
             */
            virtual std::string booleanField(const std::string& colunm_name,bool nullable) const = 0;

            /**
             * \brief create a charField culumn
             * \param colunm_name the column name
             * \param max_length the max length to store
             */
            virtual std::string charField(const std::string& colunm_name,unsigned int max_length,bool nullable) const = 0;

            /**
             * \brief create a commaSeparatedIntegerField culumn
             * \param colunm_name the column name
             * \param max_length the max length to store
             */
            //virtual std::string commaSeparatedIntegerField(const std::string& colunm_nameunsigned int max_length,bool nullable) const = 0;

            /**
             * \brief create a dateField culumn
             * \param colunm_name the column name
             */
            virtual std::string dateField(const std::string& colunm_name,bool nullable) const = 0;

            /**
             * \brief create a dateTimeField culumn
             * \param colunm_name the column name
             */
            virtual std::string dateTimeField(const std::string& colunm_name,bool nullable) const = 0;

            /**
             * \brief create a decimalField culumn
             * \param colunm_name the column name
             * \param max_digits is the number of digits to store
             * \param decimal_places ins the number of décimal
             */
            virtual std::string decimalField(const std::string& colunm_name,unsigned int max_digits,unsigned int decimal_places,bool nullable) const = 0;


            /**
             * \brief create a floatField culumn
             * \param colunm_name the column name
             */
            virtual std::string floatField(const std::string& colunm_name,bool nullable) const = 0;

            /**
             * \brief create a doubleField culumn
             * \param colunm_name the column name
             */
            virtual std::string doubleField(const std::string& colunm_name,bool nullable) const = 0;

            /**
             * \brief create a integerField culumn
             * \param colunm_name the column name
             */
            virtual std::string integerField(const std::string& colunm_name,bool nullable) const = 0;

            /**
             * \brief create a bigIntegerField culumn
             * \param colunm_name the column name
             */
            virtual std::string bigIntegerField(const std::string& colunm_name,bool nullable) const = 0;

            /**
             * \brief create a oneToOneField culumn
             * \param colunm_name the column name
             */
            virtual std::string oneToOneField(const std::string& colunm_name,bool nullable) const = 0;

            /**
             * \brief create a ForeignKey culumn
             * \param colunm_name the column name
             * \param table the table to link with
             * \param nullable if the collum can be null
             */
            virtual std::string fk(const std::string& colunm_name,const std::string& table,bool nullable) const = 0;

            /**
             * \brief create a positiveIntegerField culumn
             * \param colunm_name the column name
             */
            virtual std::string positiveIntegerField(const std::string& colunm_name,bool nullable) const = 0;

            /**
             * \brief create a positiveSmallIntegerField culumn
             * \param colunm_name the column name
             */
            virtual std::string positiveSmallIntegerField(const std::string& colunm_name,bool nullable) const = 0;

            /**
             * \brief create a smallIntegerField culumn
             * \param colunm_name the column name
             */
            virtual std::string smallIntegerField(const std::string& colunm_name,bool nullable) const = 0;

            /**
             * \brief create a textField culumn
             * \param colunm_name the column name
             */
            virtual std::string textField(const std::string& colunm_name,bool nullable) const = 0;

            /**
             * \brief create a timeField culumn
             * \param colunm_name the column name
             */
            virtual std::string timeField(const std::string& colunm_name,bool nullable) const = 0;

            /**
             * \brief create a binaryField culumn
             * \param colunm_name the column name
             */
            //virtual std::string binaryField(const std::string& colunm_name,bool nullable) const = 0;


        protected:
            TableCreator();
            TableCreator(const TableCreator&) = delete;
            TableCreator& operator=(const TableCreator&)= delete;

    };
}
#endif
