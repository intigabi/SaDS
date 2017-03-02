// HW 3
// Inti Mendoza

#include <iostream>
#include <vector>
using namespace std;

class NAME {
public:
	string name;
};

class COMM {
};

class fun_COMM : COMM {
public:
	NAME name;
	NAME arg;
	COMM comm;
};

class shell_COMM : COMM {
public:
	NAME name;
	vector<EXPR> exprs;
};

class call_COMM : COMM {
public:
	NAME name;
	EXPR expr;
};

class comm_COMM : COMM {
public:
	COMM comm0;
	COMM comm1;
};

class EXPR {
};

class var_EXPR : EXPR {
	NAME name;
};

class str_EXPR : EXPR {
	string str;
};


EXPR parse_EXPR(string expr) {
	string str = "";

	var_EXPR var;
	str_EXPR str_e;

	if(expr[0] == '"') {
		for(int i = 0; i < expr.len(); i++) {
			str += expr[i];
		}
		str_e.str = str;
		return str_e;
	} else {
		var.name = str;
		return var;
	}
	return NULL;
}

COMM parse_COMM(string comm) {
	string name0, name1, comm0, comm1, expr;
	name0 = name1 = comm0 = comm1 = expr = "";
	fun_COMM fun;
	shell_COMM shell;
	call_COMM call;
	comm_COMM rec;
	if(comm == NULL)
		exit(0);
	for(int j = 0; j <= comm.len(); j++) {
		comm0 += comm[j];
		if(str[j] == ';') {
			rec.comm0 = parse_COMM(comm0);
			for(j; j < comm.len(); j++) {
				comm1 += comm[j];
			}
			rec.comm1 = parse_COMM(comm1);
			return rec;
		}
	}
	if(comm[0] == 'f') {
		int k, i;
		for(i = 4; comm[i] != '('; i++) {
			name0 += comm[i];
			k = ++i;
		}
		for(k; comm[k] != ')'; k++) {
			name1 += comm[k];
			i = ++k;
		}
		i++;
		for(i; comm[i] != '}') {
			comm0 += comm[i];
		}
		fun.comm = parse_COMM(comm0);
		fun.name = name0;
		fun.arg = name1;
		return fun;
	}
	if(comm[0] == 'r') {
		int k, i;
		for(i = 4; comm[i] != '('; i++) {
			name0 += comm[i];
			k = ++i;
		}
		vector<EXPR>::exprs;
		string expr = "";
		for(++k; comm[k] != ')'; k++) {
			if(comm[k] == ' ') {
				exprs.push_back(parse_EXPR(expr));
				expr = "";
			} else {
				expr += comm[k];
			}
		}
		shell.name = name0;
		shell.exprs = exprs;
		return shell;
	}
	int o, p;
	for(o = 0; comm[o] != '('; o++) {
		name0 += comm[o];
		p = ++o;
	}
	for(p; comm[p] != ')'; p++) {
		expr += comm[p];
	}
	call.name = name0;
	call.expr = parse_EXPR(expr);
	return call;
}

int Interpreter(string parse) {
	if(parse_EXPR(parse) == NULL) {
		parse_COMM(parse);
	}
	return 0;
}

int main() {
	string parse;
	cin >> parse;
	return Interpreter(parse);
}
