/**
 * @file align_eigen_comma_init.cpp
 *
 * @author  Matthew Woehlke
 * copied/adapted from align_left_shift.cpp
 * @author  Guy Maurel
 * @author  Ben Gardner
 * @license GPL v2+
 */

#include "align_eigen_comma_init.h"

#include "align_stack.h"
#include "indent.h"
#include "log_rules.h"

constexpr static auto LCURRENT = LALIGN;

using namespace uncrustify;


void align_eigen_comma_init(void)
{
   LOG_FUNC_ENTRY();

   Chunk      *start = Chunk::NullChunkPtr;
   AlignStack as;

   as.Start(255);

   Chunk *pc = Chunk::get_head();

   while (pc->isNotNullChunk())
   {
      if (chunk_is_newline(pc))
      {
         LOG_FMT(LALIGN, "%s(%d): orig_line is %zu, <Newline>\n", __func__, __LINE__, pc->orig_line);
      }
      else
      {
         LOG_FMT(LALIGN, "%s(%d): orig_line is %zu, orig_col is %zu, pc->text() '%s'\n",
                 __func__, __LINE__, pc->orig_line, pc->orig_col, pc->text());
      }

      if (  start->isNotNullChunk()
         && ((pc->flags & PCF_IN_PREPROC) != (start->flags & PCF_IN_PREPROC)))
      {
         // a change in preproc status restarts the aligning
         as.Flush();
         start = Chunk::NullChunkPtr;
      }
      else if (chunk_is_newline(pc))
      {
         as.NewLines(pc->nl_count);
      }
      else if (  start->isNotNullChunk()
              && pc->level < start->level)
      {
         // A drop in level restarts the aligning
         as.Flush();
         start = Chunk::NullChunkPtr;
      }
      else if (  start->isNotNullChunk()
              && pc->level > start->level)
      {
         // Ignore any deeper levels when aligning
      }
      else if (chunk_is_token(pc, CT_SEMICOLON))
      {
         // A semicolon at the same level flushes
         as.Flush();
         start = Chunk::NullChunkPtr;
      }
      else if (  !pc->flags.test(PCF_IN_ENUM)
              && !pc->flags.test(PCF_IN_TYPEDEF)
              && chunk_is_str(pc, "<<", 2))
      {
         if (get_chunk_parent_type(pc) == CT_OPERATOR)
         {
            // Ignore operator<<
         }
         else
         {
            /*
             * check if the first one is actually on a blank line and then
             * indent it. Eg:
             *
             *      cout
             *          << "something";
             */
            Chunk *prev = pc->get_prev();

            if (  prev->isNotNullChunk()
               && chunk_is_newline(prev))
            {
               log_rule_B("indent_columns");
               indent_to_column(pc, pc->column_indent + options::indent_columns());
               pc->column_indent = pc->column;
               chunk_flags_set(pc, PCF_DONT_INDENT);
            }
            // Restart alignment
            as.Flush();
            as.Add(pc->get_next());
            start = pc;
         }
      }
      else if (!as.m_aligned.Empty())
      {
         Chunk *prev = pc->get_prev();

         if (  chunk_is_newline(prev)
            && chunk_is_token(chunk_get_prev_nc_nnl(pc), CT_COMMA))
         {
            log_rule_B("align_eigen_comma_init");
            as.Add(pc);
         }
      }
      pc = pc->get_next();
   }
   as.End();
} // align_left_shift
