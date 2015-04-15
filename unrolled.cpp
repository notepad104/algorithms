#include <assert.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>

#define QL_MAXSIZE 14
#define QL_LIMIT 7
#define ql_true 1
#define ql_false 0

    typedef int ql_bool;
    typedef struct quicklist quicklist;
    typedef struct ql_iter {
        struct quicklist *l, **lp;
        int i;
    } ql_iter;
    typedef void (*ql_cbx)(void *entry, void *more);
    typedef void (*ql_cb)(void *entry);

    ql_iter qli_init(struct quicklist **qlp);
    ql_bool qli_more(ql_iter iter);
    void * qli_get(ql_iter iter);
    void * qli_next(struct ql_iter *iter);
    void qli_delete(struct ql_iter *iter);

    void ql_map_reduce(struct quicklist *ql, void (*mapfunc)(void *entry, void *data), void(*reducefunc)(void *data, void *result), void *data, void *result);

    void * ql_get(const struct quicklist *ql, int qi);
    int ql_length(const struct quicklist *ql);
    void ql_free(struct quicklist *ql);
    ql_bool ql_empty(const struct quicklist *ql);

    struct quicklist * ql_push(struct quicklist **qlp, void *data);
    int ql_delete(struct quicklist **qlp, int index);
    ql_bool ql_find(struct quicklist **qlp, int *index, const void *value, ql_bool(*equal)(const void *, const void *));
    int ql_insert(struct quicklist **qlp, int index, void *data);
    void ql_foreach(struct quicklist *ql, ql_cb cb);
    void ql_foreachx(struct quicklist *ql, ql_cbx cb, void *);
    int ql_advance(struct quicklist **iterator, int *index, int stride);
    void *ql_replace(struct quicklist *ql, int index, void *data);

    /* you can use it as a set (sorted pointers)*/
    ql_bool ql_set_insert(struct quicklist **qlp, void *data);
    ql_bool ql_set_find(struct quicklist **qlp, int *qip, const void *data);
    ql_bool ql_set_remove(struct quicklist **qlp, const void *data);
    
struct quicklist
{
    struct quicklist *next;
    int num_elements;
    void *elements[QL_MAXSIZE];
};

ql_bool ql_find(quicklist **qlp, int *index, const void *value, ql_bool(*match)(const void *, const void *))
{
    for (;*qlp;ql_advance(qlp, index, 1)) {
        void *x = ql_get(*qlp, *index);
        if (match ? match(value, x) : value==x) {
            return ql_true;
        }
    }
    return ql_false;
}

void *ql_get(const quicklist * ql, int i)
{
    assert(ql);
    return (i < ql->num_elements) ? ql->elements[i] : ql_get(ql->next, i - ql->num_elements);
}

void *ql_replace(quicklist * ql, int i, void *data)
{
    assert(ql);
    if (i < ql->num_elements) {
        void *orig = ql->elements[i];
        ql->elements[i] = data;
        return orig;
    } else {
        return ql_replace(ql->next, i - ql->num_elements, data);
    }
}

int ql_length(const quicklist * ql)
{
    return ql ? ql->num_elements + ql_length(ql->next) : 0;
}

ql_bool ql_empty(const quicklist * ql)
{
    return !ql;
}

quicklist * ql_push(quicklist ** qlp, void *data)
{
  quicklist *ql = 0;
  while (*qlp && ((*qlp)->next || (*qlp)->num_elements == QL_MAXSIZE)) {
    qlp = &(*qlp)->next;
  }
  if (!*qlp) {
    ql = (quicklist *) malloc(sizeof(quicklist));
    if (ql) {
        ql->num_elements = 0;
        ql->next = 0;
        *qlp = ql;
    }
  } else {
    ql = *qlp;
  }
  if (ql) {
      ql->elements[ql->num_elements++] = data;
  }
  return ql;
}

int ql_delete(quicklist ** qlp, int i)
{
  quicklist *ql = *qlp;
  if (i < 0)
    return EINVAL;
  if (ql && i >= ql->num_elements) {
    return ql_delete(&ql->next, i - ql->num_elements);
  } else if (ql) {
    if (i + 1 < ql->num_elements) {
      memmove(ql->elements + i, ql->elements + i + 1,
        (ql->num_elements - i - 1) * sizeof(void *));
    }
    --ql->num_elements;
    if (ql->num_elements == 0) {
      *qlp = ql->next;
      free(ql);
    } else if (ql->next && ql->num_elements <= QL_LIMIT) {
      quicklist *qn = ql->next;
      if (ql->num_elements + qn->num_elements > QL_MAXSIZE) {
        memcpy(ql->elements + ql->num_elements, qn->elements, sizeof(void *));
        --qn->num_elements;
        ++ql->num_elements;
        memmove(qn->elements, qn->elements + 1,
          qn->num_elements * sizeof(void *));
      } else {
        memcpy(ql->elements + ql->num_elements, qn->elements,
          qn->num_elements * sizeof(void *));
        ql->num_elements += qn->num_elements;
        ql->next = qn->next;
        free(qn);
      }
    }
  }
  return 0;
}

int ql_insert(quicklist ** qlp, int i, void *data)
{
  quicklist *ql = *qlp;
  if (ql) {
    if (i >= QL_MAXSIZE) {
      return ql_insert(&ql->next, i - ql->num_elements, data);
    } else if (ql->num_elements < QL_MAXSIZE) {
      memmove(ql->elements + i + 1, ql->elements + i,
        (ql->num_elements - i) * sizeof(void *));
      ql->elements[i] = data;
      ++ql->num_elements;
    } else {
      quicklist *qn = (quicklist *) malloc(sizeof(quicklist));
      if (qn) {
          qn->next = ql->next;
          ql->next = qn;
          qn->num_elements = ql->num_elements-QL_LIMIT;
          ql->num_elements = QL_LIMIT;
          memcpy(qn->elements, ql->elements + ql->num_elements,
            QL_LIMIT * sizeof(void *));
      }
      if (i <= ql->num_elements) {
        return ql_insert(qlp, i, data);
      } else {
        return ql_insert(&ql->next, i - ql->num_elements, data);
      }
    }
  } else if (i == 0) {
    ql_push(qlp, data);
  } else {
    return EINVAL;
  }
  return 0;
}

void ql_foreach(struct quicklist *ql, void (*cb) (void *))
{
  for (; ql; ql = ql->next) {
    int i;
    for (i = 0; i != ql->num_elements; ++i) {
      cb(ql->elements[i]);
    }
  }
}

void ql_foreachx(struct quicklist *ql, void (*cb) (void *, void *), void *x)
{
  for (; ql; ql = ql->next) {
    int i;
    for (i = 0; i != ql->num_elements; ++i) {
      cb(ql->elements[i], x);
    }
  }
}

int ql_advance(struct quicklist **iterator, int *index, int stride)
{
  quicklist *ql = *iterator;
  int i = *index;
  if (!ql || i < 0 || stride < 0) {
    return ERANGE;
  } else if (i + stride < ql->num_elements) {
    *index = i + stride;
    return 0;
  } else {
    *index = i - ql->num_elements + stride;
    *iterator = ql->next;
    return ql_advance(iterator, index, 0);
  }
}

void ql_free(struct quicklist *ql)
{
  while (ql) {
    quicklist * qn = ql;
    ql = ql->next;
    free(qn);
  }
}

ql_bool ql_set_remove(struct quicklist **qlp, const void *data)
{
  int qi;
  quicklist *ql = *qlp;

  if (!ql)
    return ql_false;

  for (qi = 0; qi != ql->num_elements; ++qi) {
    void *qd = ql_get(ql, qi);
    if (qd == data) {
      return ql_delete(qlp, qi) == 0;
    }
  }
  return ql_set_remove(&ql->next, data);
}

ql_bool ql_set_insert(struct quicklist **qlp, void *data)
{
  if (*qlp) {
    quicklist *ql = *qlp;
    if (ql->num_elements > 0 && ql->elements[ql->num_elements - 1] < data) {
      if (ql->num_elements == QL_MAXSIZE || (ql->next
          && ql->next->elements[0] <= data)) {
        return ql_set_insert(&ql->next, data);
      } else {
        ql->elements[ql->num_elements++] = data;
      }
      return ql_true;
    } else {
      int i;
      /* TODO: OPT | binary search */
      for (i = 0; i != ql->num_elements; ++i) {
        if (data < ql->elements[i]) {
          ql_insert(qlp, i, data);
          return ql_true;
        }
        if (data == ql->elements[i]) {
          return ql_false;
        }
      }
    }
  }
  ql_push(qlp, data);
  return ql_true;
}

ql_bool ql_set_find(struct quicklist **qlp, int *qip, const void *data)
{
  quicklist *ql = *qlp;
  int qi;

  while (ql && ql->elements[ql->num_elements - 1] < data) {
    ql = ql->next;
  }

  if (!ql)
    return ql_false;

  /* TODO: OPT | binary search */
  for (qi = 0; qi != ql->num_elements; ++qi) {
    if (ql->elements[qi] > data) {
      return ql_false;
    }
    if (ql->elements[qi] == data) {
      if (qip) {
        *qip = qi;
        *qlp = ql;
      }
      return ql_true;
    }
  }
  return ql_false;
}

struct ql_iter qli_init(struct quicklist **qlp) {
  ql_iter iter = { 0 };
  iter.l = *qlp;
  iter.lp = qlp;
  return iter;
}

ql_bool qli_more(ql_iter iter) {
    quicklist * ql = iter.l;
    int qi = iter.i;
    if (ql) {
        if (qi>=ql->num_elements) {
            iter.l = ql->next;
            iter.i = qi - ql->num_elements;
            return qli_more(iter);
        }
        return qi<ql->num_elements;
    }
    return ql_false;
}

void * qli_next(struct ql_iter *iter) {
    void * result = ql_get(iter->l, iter->i);
    ql_advance(&iter->l, &iter->i, 1);
    return result;
}

void * qli_get(struct ql_iter iter) {
    return ql_get(iter.l, iter.i);
}

void qli_delete(struct ql_iter *iter) {
    quicklist * ql = iter->l;
    ql_delete(&iter->l, iter->i);
    if (iter->l!=ql && *(iter->lp)==ql) {
        *(iter->lp) = iter->l;
    }
}

void ql_map_reduce(struct quicklist *ql, void (*mapfunc)(void *entry, void *data), void(*reducefunc)(void *data, void *result), void *data, void *result)
{
  int qi;
  for (qi = 0; ql; ql_advance(&ql, &qi, 1)) {
    mapfunc(ql_get(ql, qi), data);
    reducefunc(data, result);
  }
}
