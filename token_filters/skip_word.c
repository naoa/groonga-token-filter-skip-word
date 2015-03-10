#include <groonga/token_filter.h>
#include <string.h>

#ifdef __GNUC__
#  define GNUC_UNUSED __attribute__((__unused__))
#else
#  define GNUC_UNUSED
#endif

#define SKIP_WORD_WITH_POSITION_TABLE_NAME "skip_word_with_positions"

typedef struct {
  grn_tokenizer_token token;
  grn_obj *table;
  grn_obj value;
} grn_skip_word_with_position_token_filter;

static void *
skip_word_with_position_init(grn_ctx *ctx, GNUC_UNUSED grn_obj *table, GNUC_UNUSED grn_token_mode mode)
{
  grn_skip_word_with_position_token_filter *token_filter;

  token_filter = GRN_PLUGIN_MALLOC(ctx, sizeof(grn_skip_word_with_position_token_filter));
  if (!token_filter) {
    GRN_PLUGIN_ERROR(ctx, GRN_NO_MEMORY_AVAILABLE,
                     "[token-filter][skip-word-with-position] "
                     "failed to allocate grn_skip_word_with_position_token_filter");
    return NULL;
  }
  token_filter->table = grn_ctx_get(ctx,
                                    SKIP_WORD_WITH_POSITION_TABLE_NAME,
                                    strlen(SKIP_WORD_WITH_POSITION_TABLE_NAME));

  if (!token_filter->table) {
    GRN_PLUGIN_ERROR(ctx, GRN_NO_MEMORY_AVAILABLE,
                     "[token-filter][skip-word-with-positon] "
                     "couldn't open a table");
    GRN_PLUGIN_FREE(ctx, token_filter);
    return NULL;
  }

  grn_tokenizer_token_init(ctx, &(token_filter->token));

  return token_filter;
}

static void
skip_word_with_position_filter(grn_ctx *ctx,
                   grn_token *current_token,
                   grn_token *next_token,
                   void *user_data)
{
  grn_skip_word_with_position_token_filter *token_filter = user_data;
  grn_obj *data;
  grn_tokenizer_status status;
  data = grn_token_get_data(ctx, current_token);

  {
    grn_id id;
    id = grn_table_get(ctx, token_filter->table,
                       GRN_TEXT_VALUE(data), GRN_TEXT_LEN(data));
    if (id != GRN_ID_NIL) {
      status = grn_token_get_status(ctx, current_token);
      status |= GRN_TOKENIZER_TOKEN_SKIP_WITH_POSITION;
      grn_token_set_status(ctx, next_token, status);
    }
  }
}

static void
skip_word_with_position_fin(grn_ctx *ctx, void *user_data)
{
  grn_skip_word_with_position_token_filter *token_filter = user_data;
  if (!token_filter) {
    return;
  }
  if (token_filter->table) {
    grn_obj_unlink(ctx, token_filter->table);
  }
  grn_tokenizer_token_fin(ctx, &(token_filter->token));
  GRN_PLUGIN_FREE(ctx, token_filter);
}

#define SKIP_WORD_TABLE_NAME "skip_words"

typedef struct {
  grn_tokenizer_token token;
  grn_obj *table;
  grn_obj value;
} grn_skip_word_token_filter;

static void *
skip_word_init(grn_ctx *ctx, GNUC_UNUSED grn_obj *table, GNUC_UNUSED grn_token_mode mode)
{
  grn_skip_word_token_filter *token_filter;

  token_filter = GRN_PLUGIN_MALLOC(ctx, sizeof(grn_skip_word_token_filter));
  if (!token_filter) {
    GRN_PLUGIN_ERROR(ctx, GRN_NO_MEMORY_AVAILABLE,
                     "[token-filter][skip-word] "
                     "failed to allocate grn_skip_word_token_filter");
    return NULL;
  }
  token_filter->table = grn_ctx_get(ctx,
                                    SKIP_WORD_TABLE_NAME,
                                    strlen(SKIP_WORD_TABLE_NAME));
  if (!token_filter->table) {
    GRN_PLUGIN_ERROR(ctx, GRN_NO_MEMORY_AVAILABLE,
                     "[token-filter][skip-word] "
                     "couldn't open a table");
    GRN_PLUGIN_FREE(ctx, token_filter);
    return NULL;
  }

  grn_tokenizer_token_init(ctx, &(token_filter->token));

  return token_filter;
}

static void
skip_word_filter(grn_ctx *ctx,
                   grn_token *current_token,
                   grn_token *next_token,
                   void *user_data)
{
  grn_skip_word_token_filter *token_filter = user_data;
  grn_obj *data;
  grn_tokenizer_status status;
  data = grn_token_get_data(ctx, current_token);

  {
    grn_id id;
    id = grn_table_get(ctx, token_filter->table,
                       GRN_TEXT_VALUE(data), GRN_TEXT_LEN(data));
    if (id != GRN_ID_NIL) {
      status = grn_token_get_status(ctx, current_token);
      status |= GRN_TOKENIZER_TOKEN_SKIP;
      grn_token_set_status(ctx, next_token, status);
    }
  }
}

static void
skip_word_fin(grn_ctx *ctx, void *user_data)
{
  grn_skip_word_token_filter *token_filter = user_data;
  if (!token_filter) {
    return;
  }
  if (token_filter->table) {
    grn_obj_unlink(ctx, token_filter->table);
  }
  grn_tokenizer_token_fin(ctx, &(token_filter->token));
  GRN_PLUGIN_FREE(ctx, token_filter);
}

grn_rc
GRN_PLUGIN_INIT(grn_ctx *ctx)
{
  return ctx->rc;
}

grn_rc
GRN_PLUGIN_REGISTER(grn_ctx *ctx)
{
  grn_rc rc;

  rc = grn_token_filter_register(ctx,
                                 "TokenFilterSkipWordWithPosition", -1,
                                 skip_word_with_position_init,
                                 skip_word_with_position_filter,
                                 skip_word_with_position_fin);

  rc = grn_token_filter_register(ctx,
                                 "TokenFilterSkipWord", -1,
                                 skip_word_init,
                                 skip_word_filter,
                                 skip_word_fin);

  return rc;
}

grn_rc
GRN_PLUGIN_FIN(GNUC_UNUSED grn_ctx *ctx)
{

  return GRN_SUCCESS;
}
