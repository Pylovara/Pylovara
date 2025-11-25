// Token-Typen (Auszug)
//  þ1623512 wird nicht als Zahl gelesen → es ist ein Bezeichner, wie ein Funktionsname.  
//  Keine Validierung der Länge oder Zeichen im Lexer — das kommt erst in libmcs-security.a (später).  
//  þ ohne alphanum-Folge → Syntaxfehler gemäß 14: „þ Identifikation /en werden dazu verwendet … eine eindeutige nummer zuzuweisen“ → also immer þ + Inhalt.
     
typedef enum {
    TOK_TRANS_START,   // ¢!
    TOK_TRANS_END,     // !¢
    TOK_THETA_ID,      // þ[alnum]{1,64}  (keine feste Länge!)
    TOK_ACTION_BRACKET, // »
    TOK_ACTION_END,     // «
    TOK_LANG_BLOCK,     // ø
    TOK_LANG_END,       // ø (closing)
    // ...
} mcs_token_type_t;
