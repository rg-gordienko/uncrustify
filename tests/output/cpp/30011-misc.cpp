
/* Not detected as a prototype? Spacing wrong. */
static struct my_entry *get_first_entry(const CHAR *blah);
static CFooo::entry *get_next_entry(const CHAR *blah);
static struct my_entry *get_next_entry(const CHAR *blah);

/* Not handling prototype params: */
typedef void (*function_name)(my_t *p_my, int foo);
typedef void (*function_name)(my_t *, int);

typedef enum
{
   one                               = 1,
   three                             = 3,
   five_hundred                      = 5,
   a_really_really_big_number        = 6,
   two                               = 7,
   a_really_really_really_big_number = 8,
} yuck_t;

const char *names[] =
{
   one                               = "one",
   three                             = "three",
   five_hundred                      = "five_hundred",
   a_really_really_big_number        = "a_really_really_big_number",
   two                               = "two",
   a_really_really_really_big_number = "a_really_really_really_big_number",
};

bool foo(char c)
{
   /* space between ] and ( */
   function_list[idx](param);

   /* Indenting with multiple members: */
   sass.asdfvas->asdfasd[asdfasdf].
      asdfasdf = 5;

   dookie::wookie << "asd"
                  << "bag"
                  << "sag";
}

#ifndef abc

#define abc    123 /* some comment */

#endif             /* another comment
