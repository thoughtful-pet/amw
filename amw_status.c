#include <amw.h>

UwTypeId UwTypeId_AmwStatus = 0;

uint16_t AMW_END_OF_BLOCK = 0;
uint16_t AMW_PARSE_ERROR = 0;

static UwResult amw_status_init(UwValuePtr self, va_list ap)
{
    AmwStatusData* data = _amw_status_data_ptr(self);
    data->line_number = 0;
    data->position = 0;

    // no need to call super method

    return UwOK();
}

static void amw_status_fini(UwValuePtr self)
{
    // call super method
    _uw_types[UwTypeId_Status]->_fini(self);
}

static void amw_status_hash(UwValuePtr self, UwHashContext* ctx)
{
    AmwStatusData* data = _amw_status_data_ptr(self);

    _uw_hash_uint64(ctx, self->type_id);
    _uw_hash_uint64(ctx, data->line_number);
    _uw_hash_uint64(ctx, data->position);
    // call super method
    _uw_types[UwTypeId_Status]->_hash(self, ctx);
}

static UwResult amw_status_deepcopy(UwValuePtr self)
{
    return UwError(UW_ERROR_NOT_IMPLEMENTED);
}

static void amw_status_dump(UwValuePtr self, FILE* fp, int first_indent, int next_indent, _UwCompoundChain* tail)
{
    AmwStatusData* data = _amw_status_data_ptr(self);

    _uw_dump_start(fp, self, first_indent);
    _uw_dump_base_extra_data(fp, self->extra_data);

    UwValue desc = uw_status_desc(self);
    UW_CSTRING_LOCAL(desc_cstr, &desc);
    fprintf(fp, " line %u, position %u: %s\n",
            data->line_number, data->position, desc_cstr);
}

static UwResult amw_status_to_string(UwValuePtr self)
{
    return UwError(UW_ERROR_NOT_IMPLEMENTED);
}

static bool amw_status_is_true(UwValuePtr self)
{
    // XXX
    return false;
}

static bool amw_status_equal_sametype(UwValuePtr self, UwValuePtr other)
{
    // XXX
    return false;
}

static bool amw_status_equal(UwValuePtr self, UwValuePtr other)
{
    // XXX
    return false;
}

static UwType amw_status_type;

[[ gnu::constructor ]]
static void init_amw_status()
{
    UwTypeId_AmwStatus = uw_subtype(&amw_status_type, "AmwStatus", UwTypeId_Status, sizeof(AmwStatusData));
    amw_status_type._create         = _uw_default_create,
    amw_status_type._init           = amw_status_init,
    amw_status_type._fini           = amw_status_fini,
    amw_status_type._hash           = amw_status_hash,
    amw_status_type._deepcopy       = amw_status_deepcopy,
    amw_status_type._dump           = amw_status_dump,
    amw_status_type._to_string      = amw_status_to_string,
    amw_status_type._is_true        = amw_status_is_true,
    amw_status_type._equal_sametype = amw_status_equal_sametype,
    amw_status_type._equal          = amw_status_equal,

    // init status codes
    AMW_END_OF_BLOCK = uw_define_status("END_OF_BLOCK");
    AMW_PARSE_ERROR  = uw_define_status("PARSE_ERROR");
}
