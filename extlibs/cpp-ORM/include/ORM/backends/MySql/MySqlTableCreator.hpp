#ifndef ORM_MYSQLTABLECREATOR_HPP
#define ORM_MYSQLTABLECREATOR_HPP

#include <ORM/backends/private/TableCreator.hpp>

namespace orm
{
    class MySqlTableCreator : public TableCreator
    {
        public:
            /**
             * \brief create a autoField culumn
             * \param colunm_name the column name
             */
            virtual std::string autoField(const std::string& colunm_name)const final;

            /**
             * \brief create a booleanField culumn
             * \param colunm_name the column name
             */
            virtual std::string booleanField(const std::string& colunm_name,bool nullable)const final;

            /**
             * \brief create a charField culumn
             * \param colunm_name the column name
             * \param max_length the max length to store
             */
            virtual std::string charField(const std::string& colunm_name,unsigned int max_length,bool nullable)const final;

            /**
             * \brief create a commaSeparatedIntegerField culumn
             * \param colunm_name the column name
             * \param max_length the max length to store
             */
            //virtual std::string commaSeparatedIntegerField(const std::string& colunm_nameunsigned int max_length,bool nullable)const;

            /**
             * \brief create a dateField culumn
             * \param colunm_name the column name
             */
            virtual std::string dateField(const std::string& colunm_name,bool nullable)const final;

            /**
             * \brief create a dateTimeField culumn
             * \param colunm_name the column name
             */
            virtual std::string dateTimeField(const std::string& colunm_name,bool nullable)const final;

            /**
             * \brief create a decimalField culumn
             * \param colunm_name the column name
             * \param max_digits is the number of digits to store
             * \param decimal_places ins the number of décimal
             */
            virtual std::string decimalField(const std::string& colunm_name,unsigned int max_digits,unsigned int decimal_places,bool nullable)const final;

            /**
             * \brief create a floatField culumn
             * \param colunm_name the column name
             */
            virtual std::string floatField(const std::string& colunm_name,bool nullable)const final;

            /**
             * \brief create a doubleField culumn
             * \param colunm_name the column name
             */
            virtual std::string doubleField(const std::string& colunm_name,bool nullable)const final;

            /**
             * \brief create a integerField culumn
             * \param colunm_name the column name
             */
            virtual std::string integerField(const std::string& colunm_name,bool nullable)const final;

            /**
             * \brief create a bigIntegerField culumn
             * \param colunm_name the column name
             */
            virtual std::string bigIntegerField(const std::string& colunm_name,bool nullable)const final;

            /**
             * \brief create a oneToOneField culumn
             * \param colunm_name the column name
             */
            virtual std::string oneToOneField(const std::string& colunm_name,bool nullable)const final;

            /**
             * \brief create a ForeignKey culumn
             * \param colunm_name the column name
             * \param table the table to link with
             * \param nullable if the collum can be null
             */
            virtual std::string fk(const::std::string& colunm_name,const std::string& table,bool nullable)const final;

            /**
             * \brief create a positiveIntegerField culumn
             * \param colunm_name the column name
             */
            virtual std::string positiveIntegerField(const std::string& colunm_name,bool nullable)const final;

            /**
             * \brief create a positiveSmallIntegerField culumn
             * \param colunm_name the column name
             */
            virtual std::string positiveSmallIntegerField(const std::string& colunm_name,bool nullable)const final;

            /**
             * \brief create a smallIntegerField culumn
             * \param colunm_name the column name
             */
            virtual std::string smallIntegerField(const std::string& colunm_name,bool nullable)const final;

            /**
             * \brief create a textField culumn
             * \param colunm_name the column name
             */
            virtual std::string textField(const std::string& colunm_name,bool nullable)const final;

            /**
             * \brief create a timeField culumn
             * \param colunm_name the column name
             */
            virtual std::string timeField(const std::string& colunm_name,bool nullable)const final;

            /**
             * \brief create a binaryField culumn
             * \param colunm_name the column name
             */
            //virtual std::string binaryField(const std::string& colunm_name,bool nullable)const;

        protected:
            friend class MySqlDB;

            MySqlTableCreator();
            MySqlTableCreator(const MySqlTableCreator&) = delete;
            MySqlTableCreator& operator=(const MySqlTableCreator&) = delete;

        private:
    };
}
/**
  'CommaSeparatedIntegerField': 'varchar(%(max_length)s)',
  'EmailField' : 
  'FileField':         'varchar(%(max_length)s)',
  'FilePathField':     'varchar(%(max_length)s)',
  'IPAddressField':    'char(15)',
  'GenericIPAddressField': 'char(39)',
  'NullBooleanField':  'bool',
  'SlugField':         'varchar(%(max_length)s)',
    BinaryField : blob
  }*/
#endif
