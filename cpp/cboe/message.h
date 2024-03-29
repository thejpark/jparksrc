// message header;

namespace PITCH_CBOE {
namespace MESSAGE {
    constexpr int PREFIX_LEN = 1; // Prefix 'S' in the message
namespace ADD_ORDER {
enum FORMAT {
    TIME_STAMP = PREFIX_LEN,
    TIME_STAMP_LEN = 8,
    MESSAGE_TYPE = TIME_STAMP + TIME_STAMP_LEN,
    MESSAGE_TYPE_LEN = 1,
    ORDER_ID = MESSAGE_TYPE + MESSAGE_TYPE_LEN,
    ORDER_ID_LEN = 12,
    SIDE_INDICATOR = ORDER_ID + ORDER_ID_LEN,
    SIDE_INDICATOR_LEN = 1,
    SHARES = SIDE_INDICATOR + SIDE_INDICATOR_LEN,
    SHARES_LEN = 6,
    SYMBOL = SHARES + SHARES_LEN,
    SYMBOL_LEN = 6
};
constexpr char TYPE = 'A';
} // namespace ADD_ORDER

namespace ORDER_EXECUTED {
enum FORMAT {
    TIME_STAMP = PREFIX_LEN,
    TIME_STAMP_LEN = 8,
    MESSAGE_TYPE = TIME_STAMP + TIME_STAMP_LEN,
    MESSAGE_TYPE_LEN = 1,
    ORDER_ID = MESSAGE_TYPE + MESSAGE_TYPE_LEN,
    ORDER_ID_LEN = 12,
    SHARES = ORDER_ID + ORDER_ID_LEN,
    SHARES_LEN = 6
};
constexpr char TYPE = 'E';
} // namespace ORDER_EXECUTED

namespace TRADE {
enum FORMAT {
    TIME_STAMP = PREFIX_LEN,
    TIME_STAMP_LEN = 8,
    MESSAGE_TYPE = TIME_STAMP + TIME_STAMP_LEN,
    MESSAGE_TYPE_LEN = 1,
    ORDER_ID = MESSAGE_TYPE + MESSAGE_TYPE_LEN,
    ORDER_ID_LEN = 12,
    SIDE_INDICATOR = ORDER_ID + ORDER_ID_LEN,
    SIDE_INDICATOR_LEN = 1,
    SHARES = SIDE_INDICATOR + SIDE_INDICATOR_LEN,
    SHARES_LEN = 6,
    SYMBOL = SHARES + SHARES_LEN,
    SYMBOL_LEN = 6
};
constexpr char TYPE = 'P';
} // namespace TRADE

namespace CANCEL_ORDER {
enum FORMAT {
    TIME_STAMP = PREFIX_LEN,
    TIME_STAMP_LEN = 8,
    MESSAGE_TYPE = TIME_STAMP + TIME_STAMP_LEN,
    MESSAGE_TYPE_LEN = 1,
    ORDER_ID = MESSAGE_TYPE + MESSAGE_TYPE_LEN,
    ORDER_ID_LEN = 12,
    SHARES = ORDER_ID + ORDER_ID_LEN,
    SHARES_LEN = 6,
};
constexpr char TYPE = 'X';
} // namespace CANCEL_ORDER

} // namespace MESSAGE

} // namespace PITCH_CBOE
