/******************************************************************************
 *
 * Copyright (c) 2017, the Perspective Authors.
 *
 * This file is part of the Perspective library, distributed under the terms of
 * the Apache License 2.0.  The full license can be found in the LICENSE file.
 *
 */

#include <perspective/first.h>
#include <perspective/schema.h>

namespace perspective {

t_schema_recipe::t_schema_recipe() {}

t_schema::t_schema() {}

t_schema::t_schema(const t_schema_recipe& recipe)
    : t_schema(recipe.m_columns, recipe.m_types) {}

t_schema::t_schema(const std::vector<std::string>& columns, const std::vector<t_dtype>& types)
    : m_columns(columns)
    , m_types(types)
    , m_status_enabled(columns.size())
    , m_pkeyidx(0)
    , m_opidx(0) {
    PSP_VERBOSE_ASSERT(columns.size() == types.size(), "Size mismatch");

    bool pkey_found = false;
    bool op_found = false;

    std::string pkey_str("psp_pkey");
    std::string op_str("psp_op");
    for (std::vector<std::string>::size_type idx = 0, loop_end = types.size(); idx < loop_end;
         ++idx) {
        m_colidx_map[columns[idx]] = idx;
        m_coldt_map[columns[idx]] = types[idx];
        for(size_t agg_idx = t_aggtype::AGGTYPE_SUM; agg_idx <= t_aggtype::AGGTYPE_PCT_SUM_GRAND_TOTAL; agg_idx++)
        {
            m_colidx_map[columns[idx] + "(" + agg_str(agg_idx) + ")"] = idx;
            m_coldt_map[columns[idx] + "(" + agg_str(agg_idx) + ")"] = types[idx];
        }
        m_status_enabled[idx] = true;
        if (columns[idx] == pkey_str) {
            pkey_found = true;
            m_pkeyidx = idx;
        }

        if (columns[idx] == op_str) {
            op_found = true;
            m_opidx = idx;
        }
    }

    m_is_pkey = pkey_found && op_found;
}

t_uindex
t_schema::get_num_columns() const {
    return m_columns.size();
}

t_uindex
t_schema::size() const {
    return m_columns.size();
}

t_uindex
t_schema::get_colidx(const std::string& colname) const {
    auto iter = m_colidx_map.find(colname);
    if (iter == m_colidx_map.end()) {
        std::cout << "Column " << colname << " does not exist in schema." << std::endl;
        PSP_COMPLAIN_AND_ABORT("");
    }
    return iter->second;
}

t_dtype
t_schema::get_dtype(const std::string& colname) const {
    auto iter = m_coldt_map.find(colname);
    if (iter == m_coldt_map.end()) {
        std::cout << "Column " << colname << " does not exist in schema." << std::endl;
        PSP_COMPLAIN_AND_ABORT("");
    }
    return iter->second;
}

bool
t_schema::is_pkey() const {
    return m_is_pkey;
}

bool
t_schema::operator==(const t_schema& rhs) const {
    return m_columns == rhs.m_columns && m_types == rhs.m_types
        && m_status_enabled == rhs.m_status_enabled;
}

void
t_schema::add_column(const std::string& colname, t_dtype dtype) {
    t_uindex idx = m_columns.size();
    m_columns.push_back(colname);
    m_status_enabled.push_back(true);
    m_types.push_back(dtype);
    m_colidx_map[colname] = idx;
    m_coldt_map[colname] = dtype;
    for(size_t agg_idx = t_aggtype::AGGTYPE_SUM; agg_idx <= t_aggtype::AGGTYPE_PCT_SUM_GRAND_TOTAL; agg_idx++)
    {
        m_colidx_map[colname + "(" + agg_str(agg_idx) + ")"] = idx;
        m_coldt_map[colname + "(" + agg_str(agg_idx) + ")"] = dtype;
    }

    if (colname == std::string("psp_pkey")) {
        m_pkeyidx = idx;
        m_is_pkey = true;
    }

    if (colname == std::string("psp_op")) {
        m_opidx = idx;
        m_is_pkey = true;
    }
}

void
t_schema::retype_column(const std::string& colname, t_dtype dtype) {
    if (colname == std::string("psp_pkey") || colname == std::string("psp_op")) {
        PSP_COMPLAIN_AND_ABORT("Cannot retype primary key or operation columns.");
    }
    if (!has_column(colname)) {
        PSP_COMPLAIN_AND_ABORT("Cannot retype a column that does not exist.");
    }

    t_uindex idx = get_colidx(colname);
    m_types[idx] = dtype;
    m_colidx_map[colname] = idx;
    m_coldt_map[colname] = dtype;
}

t_schema_recipe
t_schema::get_recipe() const {
    t_schema_recipe rval;
    rval.m_columns = m_columns;
    rval.m_types = m_types;
    return rval;
}

bool
t_schema::has_column(const std::string& colname) const {
    auto iter = m_colidx_map.find(colname);
    return iter != m_colidx_map.end();
}

const std::vector<std::string>&
t_schema::columns() const {
    return m_columns;
}

const std::vector<t_dtype>
t_schema::types() const {
    return m_types;
}

t_table_static_ctx
t_schema::get_table_context() const {
    t_table_static_ctx rv;
    for (size_t idx = 0, loop_end = m_columns.size(); idx < loop_end; ++idx) {
        t_column_static_ctx v;
        v.m_colname = m_columns[idx];
        v.m_dtype = m_types[idx];
        rv.m_columns.push_back(v);
    }
    return rv;
}

std::string
t_schema::str() const {
    std::stringstream ss;
    ss << *this;
    return ss.str();
}

t_schema
t_schema::drop(const std::set<std::string>& columns) const {
    std::vector<std::string> cols;
    std::vector<t_dtype> types;

    for (t_uindex idx = 0, loop_end = m_columns.size(); idx < loop_end; ++idx) {
        if (columns.find(m_columns[idx]) == columns.end()) {
            cols.push_back(m_columns[idx]);
            types.push_back(m_types[idx]);
        }
    }
    return t_schema(cols, types);
}

t_schema
t_schema::operator+(const t_schema& o) const {
    t_schema rv(m_columns, m_types);
    for (t_uindex idx = 0, loop_end = o.m_columns.size(); idx < loop_end; ++idx) {
        rv.add_column(o.m_columns[idx], o.m_types[idx]);
    }
    return rv;
}

std::string
t_schema::agg_str(const size_t agg_id) const {
    switch (static_cast<t_aggtype>(agg_id)) {
        case t_aggtype::AGGTYPE_SUM: {
            return "sum";
        } break;
        case t_aggtype::AGGTYPE_SUM_ABS: {
            return "sum abs";
        } break;
        case t_aggtype::AGGTYPE_MUL: {
            return "mul";
        } break;
        case t_aggtype::AGGTYPE_COUNT: {
            return "count";
        } break;
        case t_aggtype::AGGTYPE_MEAN: {
            return "mean";
        } break;
        case t_aggtype::AGGTYPE_WEIGHTED_MEAN: {
            return "avg";
        } break;
        case t_aggtype::AGGTYPE_UNIQUE: {
            return "unique";
        } break;
        case t_aggtype::AGGTYPE_ANY: {
            return "any";
        } break;
        case t_aggtype::AGGTYPE_MEDIAN: {
            return "median";
        } break;
        case t_aggtype::AGGTYPE_JOIN: {
            return "join";
        } break;
        case t_aggtype::AGGTYPE_SCALED_DIV: {
            return "scaled div";
        } break;
        case t_aggtype::AGGTYPE_SCALED_ADD: {
            return "scaled add";
        } break;
        case t_aggtype::AGGTYPE_SCALED_MUL: {
            return "scaled mul";
        } break;
        case t_aggtype::AGGTYPE_DOMINANT: {
            return "dominant";
        } break;
        case t_aggtype::AGGTYPE_FIRST: {
            return "first by index";
        } break;
        case t_aggtype::AGGTYPE_LAST: {
            return "last by index";
        } break;
        case t_aggtype::AGGTYPE_PY_AGG: {
            return "py agg";
        } break;
        case t_aggtype::AGGTYPE_AND: {
            return "and";
        } break;
        case t_aggtype::AGGTYPE_OR: {
            return "or";
        } break;
        case t_aggtype::AGGTYPE_LAST_VALUE: {
            return "last";
        }
        case t_aggtype::AGGTYPE_HIGH_WATER_MARK: {
            return "high";
        }
        case t_aggtype::AGGTYPE_LOW_WATER_MARK: {
            return "low";
        }
        case t_aggtype::AGGTYPE_SUM_NOT_NULL: {
            return "sum not null";
        }
        case t_aggtype::AGGTYPE_MEAN_BY_COUNT: {
            return "mean by count";
        }
        case t_aggtype::AGGTYPE_IDENTITY: {
            return "identity";
        }
        case t_aggtype::AGGTYPE_DISTINCT_COUNT: {
            return "distinct count";
        }
        case t_aggtype::AGGTYPE_DISTINCT_LEAF: {
            return "distinct leaf";
        }
        case t_aggtype::AGGTYPE_PCT_SUM_PARENT: {
            return "pct sum parent";
        }
        case t_aggtype::AGGTYPE_PCT_SUM_GRAND_TOTAL: {
            return "pct sum grand total";
        }
        default: {
            PSP_COMPLAIN_AND_ABORT("Unknown agg type");
            return "unknown";
        } break;
    }
}

} 
// end namespace perspective

namespace std {

std::ostream&
operator<<(std::ostream& os, const perspective::t_schema& s) {
    using namespace perspective;
    const std::vector<std::string>& cols = s.columns();
    const std::vector<t_dtype>& types = s.types();

    os << "t_schema<\n";
    for (size_t idx = 0, loop_end = cols.size(); idx < loop_end; ++idx) {
        os << "\t" << idx << ". " << cols[idx] << ", " << get_dtype_descr(types[idx])
           << std::endl;
    }
    os << ">\n";
    return os;
}
} // namespace std
