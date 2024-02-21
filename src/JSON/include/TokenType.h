#pragma once

/**
 * @brief Enum representing different token types.
 * 
 * This enum defines various token types that can be encountered during lexical analysis.
 * The token types include LBrace, RBrace, LBracket, RBracket, Colon, Comma, String, Number,
 * True, False, Null, and Invalid.
 */
enum TokenType {
    LBrace,        /**< Left brace token */
    RBrace,        /**< Right brace token */
    LBracket,      /**< Left bracket token */
    RBracket,      /**< Right bracket token */
    Colon,         /**< Colon token */
    Comma,         /**< Comma token */
    String,        /**< String token */
    Number,        /**< Number token */
    True,          /**< True token */
    False,         /**< False token */
    Null,          /**< Null token */
    Invalid        /**< Invalid token */
};
