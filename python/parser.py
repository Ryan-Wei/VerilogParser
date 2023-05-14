import ply.yacc as yacc
import json
from lexer import tokens, lexer

# Tokens
tokens = (
    'NUMBER',
    'LPAREN',
    'RPAREN',
    'SEMICOLON',
    'MODULE',
    'ENDMODULE'
)

# Grammar rules
def p_module(p):
    'module : MODULE SEMICOLON ENDMODULE'
    p[0] = {
        'label': 'module',
        'name': p[2],
        'input': p[4],
        'body': p[7]
    }




# Build the parser
parser = yacc.yacc()

# error handling
def p_error(p):
    print(f"Syntax error at line {p.lineno}")
    print(p)

# Test input
input_text = '''module ; endmodule'''

# Parse the input and output the result as JSON
result = parser.parse(input_text)
print(json.dumps(result, indent=2))
print("end")
