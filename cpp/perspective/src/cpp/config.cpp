/******************************************************************************
 *
 * Copyright (c) 2017, the Perspective Authors.
 *
 * This file is part of the Perspective library, distributed under the terms of
 * the Apache License 2.0.  The full license can be found in the LICENSE file.
 *
 */

#include <perspective/first.h>
#include <perspective/config.h>

namespace perspective {

t_config_recipe::t_config_recipe()
    : m_child_pkey_column("psp_pkey") {}

t_config::t_config() {}

t_config::t_config(const t_config_recipe& r)
    : m_detail_columns(r.m_detail_columns)
    , m_totals(r.m_totals)
    , m_combiner(r.m_combiner)
    , m_handle_nan_sort(r.m_handle_nan_sort)
    , m_parent_pkey_column(r.m_parent_pkey_column)
    , m_child_pkey_column(r.m_child_pkey_column)
    , m_grouping_label_column(r.m_grouping_label_column)
    , m_fmode(r.m_fmode)
    , m_filter_exprs(r.m_filter_exprs)

{
    for (const auto& v : r.m_row_pivots) {
        m_row_pivots.push_back(t_pivot(v));
    }

    for (const auto& v : r.m_col_pivots) {
        m_col_pivots.push_back(t_pivot(v));
    }

    for (const auto& v : r.m_aggregates) {
        m_aggregates.push_back(t_aggspec(v));
    }

    if (m_fmode == FMODE_SIMPLE_CLAUSES) {
        for (const auto& v : r.m_fterms) {
            m_fterms.push_back(t_fterm(v));
        }
    }

    std::vector<std::string> sort_pivot;
    std::vector<std::string> sort_pivot_by;

    for (const auto& v : r.m_sortby) {
        sort_pivot.push_back(v.first);
        sort_pivot_by.push_back(v.second);
    }

    setup(m_detail_columns, sort_pivot, sort_pivot_by);
}

t_config::t_config(const std::vector<t_pivot>& row_pivots,
    const std::vector<t_pivot>& col_pivots, const std::vector<t_aggspec>& aggregates,
    const std::vector<std::string>& detail_columns, const t_totals totals,
    const std::vector<std::string>& sort_pivot, const std::vector<std::string>& sort_pivot_by,
    t_filter_op combiner, const std::vector<t_fterm>& fterms, bool handle_nan_sort,
    const std::string& parent_pkey_column, const std::string& child_pkey_column,
    const std::string& grouping_label_column, t_fmode fmode,
    const std::vector<std::string>& filter_exprs, const std::string& grand_agg_str)
    : m_row_pivots(row_pivots)
    , m_col_pivots(col_pivots)
    , m_aggregates(aggregates)
    , m_detail_columns(detail_columns)
    , m_totals(totals)
    , m_combiner(combiner)
    , m_fterms(fterms)
    , m_handle_nan_sort(handle_nan_sort)
    , m_parent_pkey_column(parent_pkey_column)
    , m_child_pkey_column(child_pkey_column)
    , m_grouping_label_column(grouping_label_column)
    , m_fmode(fmode)
    , m_filter_exprs(filter_exprs)
    , m_grand_agg_str(grand_agg_str) {
    setup(detail_columns, sort_pivot, sort_pivot_by);
}

// view config
t_config::t_config(const std::vector<std::string>& row_pivots,
    const std::vector<std::string>& col_pivots, const std::vector<t_aggspec>& aggregates,
    const std::vector<t_sortspec>& sortspecs, const std::vector<t_sortspec>& col_sortspecs,
    t_filter_op combiner, const std::vector<t_fterm>& fterms,
    const std::vector<std::string>& col_names, bool column_only)
    : m_column_only(column_only)
    , m_sortspecs(sortspecs)
    , m_col_sortspecs(col_sortspecs)
    , m_aggregates(aggregates)
    , m_detail_columns(col_names)
    , m_combiner(combiner)
    , m_fterms(fterms) {
    for (const auto& p : row_pivots) {
        m_row_pivots.push_back(t_pivot(p));
    }
    for (const auto& p : col_pivots) {
        m_col_pivots.push_back(t_pivot(p));
    }
};

t_config::t_config(
    const std::vector<t_pivot>& row_pivots, const std::vector<t_aggspec>& aggregates)
    : m_row_pivots(row_pivots)
    , m_aggregates(aggregates)
    , m_fmode(FMODE_SIMPLE_CLAUSES) {
    setup(m_detail_columns, std::vector<std::string>{}, std::vector<std::string>{});
}

// grouped_pkeys
t_config::t_config(const std::vector<std::string>& row_pivots,
    const std::vector<std::string>& detail_columns, t_filter_op combiner,
    const std::vector<t_fterm>& fterms, const std::string& parent_pkey_column,
    const std::string& child_pkey_column, const std::string& grouping_label_column)
    : m_detail_columns(detail_columns)
    , m_combiner(combiner)
    , m_fterms(fterms)
    , m_handle_nan_sort(true)
    , m_parent_pkey_column(parent_pkey_column)
    , m_child_pkey_column(child_pkey_column)
    , m_grouping_label_column(grouping_label_column)
    , m_fmode(FMODE_SIMPLE_CLAUSES)

{
    for (const auto& p : row_pivots) {
        m_row_pivots.push_back(t_pivot(p));
    }

    setup(m_detail_columns, std::vector<std::string>{}, std::vector<std::string>{});
}

// ctx2
t_config::t_config(const std::vector<std::string>& row_pivots,
    const std::vector<std::string>& col_pivots, const std::vector<t_aggspec>& aggregates)
    : t_config(row_pivots, col_pivots, aggregates, TOTALS_HIDDEN, FILTER_OP_AND, {})

{}

t_config::t_config(const std::vector<t_pivot>& row_pivots,
    const std::vector<t_pivot>& col_pivots, const std::vector<t_aggspec>& aggregates,
    const t_totals totals, t_filter_op combiner, const std::vector<t_fterm>& fterms,
    bool column_only)
    : m_row_pivots(row_pivots)
    , m_col_pivots(col_pivots)
    , m_column_only(column_only)
    , m_aggregates(aggregates)
    , m_totals(totals)
    , m_combiner(combiner)
    , m_fterms(fterms)
    , m_handle_nan_sort(true)
    , m_fmode(FMODE_SIMPLE_CLAUSES) {
    setup(m_detail_columns, std::vector<std::string>{}, std::vector<std::string>{});
}

t_config::t_config(const std::vector<std::string>& row_pivots,
    const std::vector<std::string>& col_pivots, const std::vector<t_aggspec>& aggregates,
    const t_totals totals, t_filter_op combiner, const std::vector<t_fterm>& fterms)
    : m_aggregates(aggregates)
    , m_totals(totals)
    , m_combiner(combiner)
    , m_fterms(fterms)
    , m_handle_nan_sort(true)
    , m_fmode(FMODE_SIMPLE_CLAUSES) {
    for (const auto& p : row_pivots) {
        m_row_pivots.push_back(t_pivot(p));
    }

    for (const auto& p : col_pivots) {
        m_col_pivots.push_back(t_pivot(p));
    }

    setup(m_detail_columns, std::vector<std::string>{}, std::vector<std::string>{});
}

// t_ctx1
t_config::t_config(
    const std::vector<std::string>& row_pivots, const std::vector<t_aggspec>& aggregates)
    : m_aggregates(aggregates)
    , m_totals(TOTALS_BEFORE)
    , m_combiner(FILTER_OP_AND)
    , m_handle_nan_sort(true)
    , m_fmode(FMODE_SIMPLE_CLAUSES) {
    for (const auto& p : row_pivots) {
        m_row_pivots.push_back(t_pivot(p));
    }

    setup(m_detail_columns, std::vector<std::string>{}, std::vector<std::string>{});
}

t_config::t_config(const std::vector<std::string>& row_pivots, const t_aggspec& agg)
    : m_aggregates(std::vector<t_aggspec>{agg})
    , m_totals(TOTALS_BEFORE)
    , m_combiner(FILTER_OP_AND)
    , m_handle_nan_sort(true)
    , m_fmode(FMODE_SIMPLE_CLAUSES) {
    for (const auto& p : row_pivots) {
        m_row_pivots.push_back(t_pivot(p));
    }

    setup(m_detail_columns, std::vector<std::string>{}, std::vector<std::string>{});
}

t_config::t_config(const std::vector<t_pivot>& row_pivots,
    const std::vector<t_aggspec>& aggregates, t_filter_op combiner,
    const std::vector<t_fterm>& fterms)
    : m_row_pivots(row_pivots)
    , m_aggregates(aggregates)
    , m_totals(TOTALS_BEFORE)
    , m_combiner(combiner)
    , m_fterms(fterms)
    , m_handle_nan_sort(true)
    , m_fmode(FMODE_SIMPLE_CLAUSES) {
    setup(m_detail_columns, std::vector<std::string>{}, std::vector<std::string>{});
}

t_config::t_config(const std::vector<std::string>& row_pivots,
    const std::vector<t_aggspec>& aggregates, t_filter_op combiner,
    const std::vector<t_fterm>& fterms)
    : m_aggregates(aggregates)
    , m_totals(TOTALS_BEFORE)
    , m_combiner(combiner)
    , m_fterms(fterms)
    , m_handle_nan_sort(true)
    , m_fmode(FMODE_SIMPLE_CLAUSES) {
    for (const auto& p : row_pivots) {
        m_row_pivots.push_back(t_pivot(p));
    }

    setup(m_detail_columns, std::vector<std::string>{}, std::vector<std::string>{});
}

// t_ctx0
t_config::t_config(const std::vector<std::string>& detail_columns)
    : t_config(detail_columns, FILTER_OP_AND, {}) {}

t_config::t_config(const std::vector<std::string>& detail_columns, t_filter_op combiner,
    const std::vector<t_fterm>& fterms)
    : m_detail_columns(detail_columns)
    , m_combiner(combiner)
    , m_fterms(fterms)
    , m_fmode(FMODE_SIMPLE_CLAUSES) {}

void
t_config::setup(const std::vector<std::string>& detail_columns,
    const std::vector<std::string>& sort_pivot, const std::vector<std::string>& sort_pivot_by) {
    t_index count = 0;
    for (std::vector<std::string>::const_iterator iter = detail_columns.begin();
         iter != detail_columns.end(); ++iter) {
        m_detail_colmap[*iter] = count;
        count++;
    }

    m_has_pkey_agg = false;

    for (std::vector<t_aggspec>::const_iterator iter = m_aggregates.begin();
         iter != m_aggregates.end(); ++iter) {
        switch (iter->agg()) {
            case AGGTYPE_AND:
            case AGGTYPE_OR:
            case AGGTYPE_ANY:
            case AGGTYPE_FIRST:
            case AGGTYPE_LAST:
            case AGGTYPE_MEAN:
            case AGGTYPE_WEIGHTED_MEAN:
            case AGGTYPE_UNIQUE:
            case AGGTYPE_MEDIAN:
            case AGGTYPE_JOIN:
            case AGGTYPE_DOMINANT:
            case AGGTYPE_PY_AGG:
            case AGGTYPE_SUM_NOT_NULL:
            case AGGTYPE_SUM_ABS:
            case AGGTYPE_MUL:
            case AGGTYPE_DISTINCT_COUNT:
            case AGGTYPE_DISTINCT_LEAF:
                m_has_pkey_agg = true;
                break;
            default:
                break;
        }

        if (m_has_pkey_agg)
            break;
    }

    for (t_index idx = 0, loop_end = sort_pivot.size(); idx < loop_end; ++idx) {
        m_sortby[sort_pivot[idx]] = sort_pivot_by[idx];
    }

    populate_sortby(m_row_pivots);
    populate_sortby(m_col_pivots);
}

void
t_config::populate_sortby(const std::vector<t_pivot>& pivots) {
    for (t_index idx = 0, loop_end = pivots.size(); idx < loop_end; ++idx) {
        const t_pivot& pivot = pivots[idx];

        PSP_VERBOSE_ASSERT(
            pivot.mode() == PIVOT_MODE_NORMAL, "Only normal pivots supported for now");
        std::string pstr = pivot.colname();
        if (m_sortby.find(pstr) == m_sortby.end())
            m_sortby[pstr] = pstr;
    }
}

t_index
t_config::get_colidx(const std::string& colname) const {
    std::map<std::string, t_index>::const_iterator iter = m_detail_colmap.find(colname);
    if (iter == m_detail_colmap.end()) {
        return INVALID_INDEX;
    } else {
        return iter->second;
    }
}

std::string
t_config::repr() const {
    std::stringstream ss;
    ss << "t_config<" << this << ">";
    return ss.str();
}

t_uindex
t_config::get_num_aggregates() const {
    return m_aggregates.size();
}

t_uindex
t_config::get_num_columns() const {
    return m_detail_columns.size();
}

std::string
t_config::col_at(t_uindex idx) const {
    if (idx >= m_detail_columns.size())
        return "";
    return m_detail_columns[idx];
}

bool
t_config::has_pkey_agg() const {
    return m_has_pkey_agg;
}

std::string
t_config::get_totals_string() const {
    switch (m_totals) {
        case TOTALS_BEFORE: {
            return "before";
        } break;
        case TOTALS_HIDDEN: {
            return "hidden";
        } break;
        case TOTALS_AFTER: {
            return "after";
        } break;
        default: { return "INVALID_TOTALS"; } break;
    }
}

std::string
t_config::get_sort_by(const std::string& pivot) const {
    std::string rval;
    std::map<std::string, std::string>::const_iterator iter = m_sortby.find(pivot);

    if (iter == m_sortby.end()) {
        return pivot;
    } else {
        rval = iter->second;
    }
    return rval;
}

bool
t_config::validate_colidx(t_index idx) const {
    if (idx < 0 || idx >= static_cast<t_index>(get_num_columns()))
        return false;
    return true;
}

std::vector<std::string>
t_config::get_column_names() const {
    return m_detail_columns;
}

t_uindex
t_config::get_num_rpivots() const {
    return m_row_pivots.size();
}

t_uindex
t_config::get_num_cpivots() const {
    return m_col_pivots.size();
}

bool
t_config::is_column_only() const {
    return m_column_only;
}

const std::vector<t_pivot>&
t_config::get_row_pivots() const {
    return m_row_pivots;
}

const std::vector<t_pivot>&
t_config::get_column_pivots() const {
    return m_col_pivots;
}

std::vector<std::pair<std::string, std::string>>
t_config::get_sortby_pairs() const {
    std::vector<std::pair<std::string, std::string>> rval(m_sortby.size());
    t_uindex idx = 0;
    for (std::map<std::string, std::string>::const_iterator iter = m_sortby.begin();
         iter != m_sortby.end(); ++iter) {
        rval[idx].first = iter->first;
        rval[idx].second = iter->second;
        ++idx;
    }
    return rval;
}

const std::vector<t_sortspec>&
t_config::get_sortspecs() const {
    return m_sortspecs;
}

const std::vector<t_sortspec>&
t_config::get_col_sortspecs() const {
    return m_col_sortspecs;
}

const std::vector<t_aggspec>&
t_config::get_aggregates() const {
    return m_aggregates;
}

bool
t_config::has_filters() const {
    switch (m_fmode) {
        case FMODE_SIMPLE_CLAUSES: {
            return !m_fterms.empty();
        } break;
        default: { return false; }
    }
    return false;
}

const std::vector<t_fterm>&
t_config::get_fterms() const {
    return m_fterms;
}

t_filter_op
t_config::get_combiner() const {
    return m_combiner;
}

t_totals
t_config::get_totals() const {
    return m_totals;
}

std::vector<t_pivot>
t_config::get_pivots() const {
    std::vector<t_pivot> rval = m_row_pivots;
    for (const auto& piv : m_col_pivots) {
        rval.push_back(piv);
    }
    return rval;
}

bool
t_config::handle_nan_sort() const {
    return m_handle_nan_sort;
}

std::string
t_config::get_parent_pkey_column() const {
    return m_parent_pkey_column;
}

std::string
t_config::get_child_pkey_column() const {
    return m_child_pkey_column;
}

const std::string&
t_config::get_grouping_label_column() const {
    return m_grouping_label_column;
}

t_config_recipe
t_config::get_recipe() const {
    t_config_recipe rv;

    for (const auto& p : m_row_pivots) {
        rv.m_row_pivots.push_back(p.get_recipe());
    }

    for (const auto& p : m_col_pivots) {
        rv.m_col_pivots.push_back(p.get_recipe());
    }

    rv.m_sortby = get_sortby_pairs();

    for (const auto& a : m_aggregates) {
        rv.m_aggregates.push_back(a.get_recipe());
    }

    rv.m_totals = m_totals;
    rv.m_combiner = m_combiner;

    for (const auto& ft : m_fterms) {
        rv.m_fterms.push_back(ft.get_recipe());
    }

    rv.m_handle_nan_sort = m_handle_nan_sort;
    rv.m_parent_pkey_column = m_parent_pkey_column;
    rv.m_child_pkey_column = m_child_pkey_column;
    rv.m_grouping_label_column = m_grouping_label_column;
    return rv;
}

std::string
t_config::unity_get_column_name(t_uindex idx) const {
    if (m_aggregates.empty()) {
        if (idx >= m_detail_columns.size())
            return "";
        return m_detail_columns[idx];
    }

    return m_aggregates[idx % m_aggregates.size()].name();
}

std::string
t_config::unity_get_column_display_name(t_uindex idx) const {
    if (m_aggregates.empty()) {
        if (idx >= m_detail_columns.size())
            return "";
        return m_detail_columns[idx];
    }

    return m_aggregates[idx % m_aggregates.size()].disp_name();
}

t_fmode
t_config::get_fmode() const {
    return m_fmode;
}

} // end namespace perspective
