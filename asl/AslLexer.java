// Generated from Asl.g4 by ANTLR 4.7.2
import org.antlr.v4.runtime.Lexer;
import org.antlr.v4.runtime.CharStream;
import org.antlr.v4.runtime.Token;
import org.antlr.v4.runtime.TokenStream;
import org.antlr.v4.runtime.*;
import org.antlr.v4.runtime.atn.*;
import org.antlr.v4.runtime.dfa.DFA;
import org.antlr.v4.runtime.misc.*;

@SuppressWarnings({"all", "warnings", "unchecked", "unused", "cast"})
public class AslLexer extends Lexer {
	static { RuntimeMetaData.checkVersion("4.7.2", RuntimeMetaData.VERSION); }

	protected static final DFA[] _decisionToDFA;
	protected static final PredictionContextCache _sharedContextCache =
		new PredictionContextCache();
	public static final int
		T__0=1, T__1=2, T__2=3, TRUE=4, FALSE=5, ASSIGN=6, EQUAL=7, NEQ=8, GT=9, 
		GE=10, LT=11, LE=12, NOT=13, AND=14, OR=15, PLUS=16, MINUS=17, MUL=18, 
		DIV=19, VAR=20, INT=21, FLOAT=22, CHAR=23, BOOL=24, IF=25, THEN=26, ELSE=27, 
		ENDIF=28, FUNC=29, ENDFUNC=30, READ=31, WRITE=32, LPAR=33, RPAR=34, ID=35, 
		INTVAL=36, FLOATVAL=37, CHARVAL=38, BOOLVAL=39, STRING=40, COMMENT=41, 
		WS=42;
	public static String[] channelNames = {
		"DEFAULT_TOKEN_CHANNEL", "HIDDEN"
	};

	public static String[] modeNames = {
		"DEFAULT_MODE"
	};

	private static String[] makeRuleNames() {
		return new String[] {
			"T__0", "T__1", "T__2", "TRUE", "FALSE", "ASSIGN", "EQUAL", "NEQ", "GT", 
			"GE", "LT", "LE", "NOT", "AND", "OR", "PLUS", "MINUS", "MUL", "DIV", 
			"VAR", "INT", "FLOAT", "CHAR", "BOOL", "IF", "THEN", "ELSE", "ENDIF", 
			"FUNC", "ENDFUNC", "READ", "WRITE", "LPAR", "RPAR", "ID", "INTVAL", "FLOATVAL", 
			"CHARVAL", "BOOLVAL", "STRING", "ESC_SEQ", "COMMENT", "WS"
		};
	}
	public static final String[] ruleNames = makeRuleNames();

	private static String[] makeLiteralNames() {
		return new String[] {
			null, "','", "':'", "';'", "'true'", "'false'", "'='", "'=='", "'!='", 
			"'>'", "'>='", "'<'", "'<='", "'not'", "'and'", "'or'", "'+'", "'-'", 
			"'*'", "'/'", "'var'", "'int'", "'float'", "'char'", "'bool'", "'if'", 
			"'then'", "'else'", "'endif'", "'func'", "'endfunc'", "'read'", "'write'", 
			"'('", "')'"
		};
	}
	private static final String[] _LITERAL_NAMES = makeLiteralNames();
	private static String[] makeSymbolicNames() {
		return new String[] {
			null, null, null, null, "TRUE", "FALSE", "ASSIGN", "EQUAL", "NEQ", "GT", 
			"GE", "LT", "LE", "NOT", "AND", "OR", "PLUS", "MINUS", "MUL", "DIV", 
			"VAR", "INT", "FLOAT", "CHAR", "BOOL", "IF", "THEN", "ELSE", "ENDIF", 
			"FUNC", "ENDFUNC", "READ", "WRITE", "LPAR", "RPAR", "ID", "INTVAL", "FLOATVAL", 
			"CHARVAL", "BOOLVAL", "STRING", "COMMENT", "WS"
		};
	}
	private static final String[] _SYMBOLIC_NAMES = makeSymbolicNames();
	public static final Vocabulary VOCABULARY = new VocabularyImpl(_LITERAL_NAMES, _SYMBOLIC_NAMES);

	/**
	 * @deprecated Use {@link #VOCABULARY} instead.
	 */
	@Deprecated
	public static final String[] tokenNames;
	static {
		tokenNames = new String[_SYMBOLIC_NAMES.length];
		for (int i = 0; i < tokenNames.length; i++) {
			tokenNames[i] = VOCABULARY.getLiteralName(i);
			if (tokenNames[i] == null) {
				tokenNames[i] = VOCABULARY.getSymbolicName(i);
			}

			if (tokenNames[i] == null) {
				tokenNames[i] = "<INVALID>";
			}
		}
	}

	@Override
	@Deprecated
	public String[] getTokenNames() {
		return tokenNames;
	}

	@Override

	public Vocabulary getVocabulary() {
		return VOCABULARY;
	}


	public AslLexer(CharStream input) {
		super(input);
		_interp = new LexerATNSimulator(this,_ATN,_decisionToDFA,_sharedContextCache);
	}

	@Override
	public String getGrammarFileName() { return "Asl.g4"; }

	@Override
	public String[] getRuleNames() { return ruleNames; }

	@Override
	public String getSerializedATN() { return _serializedATN; }

	@Override
	public String[] getChannelNames() { return channelNames; }

	@Override
	public String[] getModeNames() { return modeNames; }

	@Override
	public ATN getATN() { return _ATN; }

	public static final String _serializedATN =
		"\3\u608b\ua72a\u8133\ub9ed\u417c\u3be7\u7786\u5964\2,\u012b\b\1\4\2\t"+
		"\2\4\3\t\3\4\4\t\4\4\5\t\5\4\6\t\6\4\7\t\7\4\b\t\b\4\t\t\t\4\n\t\n\4\13"+
		"\t\13\4\f\t\f\4\r\t\r\4\16\t\16\4\17\t\17\4\20\t\20\4\21\t\21\4\22\t\22"+
		"\4\23\t\23\4\24\t\24\4\25\t\25\4\26\t\26\4\27\t\27\4\30\t\30\4\31\t\31"+
		"\4\32\t\32\4\33\t\33\4\34\t\34\4\35\t\35\4\36\t\36\4\37\t\37\4 \t \4!"+
		"\t!\4\"\t\"\4#\t#\4$\t$\4%\t%\4&\t&\4\'\t\'\4(\t(\4)\t)\4*\t*\4+\t+\4"+
		",\t,\3\2\3\2\3\3\3\3\3\4\3\4\3\5\3\5\3\5\3\5\3\5\3\6\3\6\3\6\3\6\3\6\3"+
		"\6\3\7\3\7\3\b\3\b\3\b\3\t\3\t\3\t\3\n\3\n\3\13\3\13\3\13\3\f\3\f\3\r"+
		"\3\r\3\r\3\16\3\16\3\16\3\16\3\17\3\17\3\17\3\17\3\20\3\20\3\20\3\21\3"+
		"\21\3\22\3\22\3\23\3\23\3\24\3\24\3\25\3\25\3\25\3\25\3\26\3\26\3\26\3"+
		"\26\3\27\3\27\3\27\3\27\3\27\3\27\3\30\3\30\3\30\3\30\3\30\3\31\3\31\3"+
		"\31\3\31\3\31\3\32\3\32\3\32\3\33\3\33\3\33\3\33\3\33\3\34\3\34\3\34\3"+
		"\34\3\34\3\35\3\35\3\35\3\35\3\35\3\35\3\36\3\36\3\36\3\36\3\36\3\37\3"+
		"\37\3\37\3\37\3\37\3\37\3\37\3\37\3 \3 \3 \3 \3 \3!\3!\3!\3!\3!\3!\3\""+
		"\3\"\3#\3#\3$\3$\7$\u00d9\n$\f$\16$\u00dc\13$\3%\6%\u00df\n%\r%\16%\u00e0"+
		"\3&\6&\u00e4\n&\r&\16&\u00e5\3&\3&\7&\u00ea\n&\f&\16&\u00ed\13&\3&\7&"+
		"\u00f0\n&\f&\16&\u00f3\13&\3&\3&\6&\u00f7\n&\r&\16&\u00f8\5&\u00fb\n&"+
		"\3\'\3\'\3\'\5\'\u0100\n\'\3\'\3\'\3(\3(\5(\u0106\n(\3)\3)\3)\7)\u010b"+
		"\n)\f)\16)\u010e\13)\3)\3)\3*\3*\3*\3+\3+\3+\3+\7+\u0119\n+\f+\16+\u011c"+
		"\13+\3+\5+\u011f\n+\3+\3+\3+\3+\3,\6,\u0126\n,\r,\16,\u0127\3,\3,\2\2"+
		"-\3\3\5\4\7\5\t\6\13\7\r\b\17\t\21\n\23\13\25\f\27\r\31\16\33\17\35\20"+
		"\37\21!\22#\23%\24\'\25)\26+\27-\30/\31\61\32\63\33\65\34\67\359\36;\37"+
		"= ?!A\"C#E$G%I&K\'M(O)Q*S\2U+W,\3\2\b\4\2C\\c|\6\2\62;C\\aac|\4\2$$^^"+
		"\n\2$$))^^ddhhppttvv\4\2\f\f\17\17\5\2\13\f\17\17\"\"\2\u0138\2\3\3\2"+
		"\2\2\2\5\3\2\2\2\2\7\3\2\2\2\2\t\3\2\2\2\2\13\3\2\2\2\2\r\3\2\2\2\2\17"+
		"\3\2\2\2\2\21\3\2\2\2\2\23\3\2\2\2\2\25\3\2\2\2\2\27\3\2\2\2\2\31\3\2"+
		"\2\2\2\33\3\2\2\2\2\35\3\2\2\2\2\37\3\2\2\2\2!\3\2\2\2\2#\3\2\2\2\2%\3"+
		"\2\2\2\2\'\3\2\2\2\2)\3\2\2\2\2+\3\2\2\2\2-\3\2\2\2\2/\3\2\2\2\2\61\3"+
		"\2\2\2\2\63\3\2\2\2\2\65\3\2\2\2\2\67\3\2\2\2\29\3\2\2\2\2;\3\2\2\2\2"+
		"=\3\2\2\2\2?\3\2\2\2\2A\3\2\2\2\2C\3\2\2\2\2E\3\2\2\2\2G\3\2\2\2\2I\3"+
		"\2\2\2\2K\3\2\2\2\2M\3\2\2\2\2O\3\2\2\2\2Q\3\2\2\2\2U\3\2\2\2\2W\3\2\2"+
		"\2\3Y\3\2\2\2\5[\3\2\2\2\7]\3\2\2\2\t_\3\2\2\2\13d\3\2\2\2\rj\3\2\2\2"+
		"\17l\3\2\2\2\21o\3\2\2\2\23r\3\2\2\2\25t\3\2\2\2\27w\3\2\2\2\31y\3\2\2"+
		"\2\33|\3\2\2\2\35\u0080\3\2\2\2\37\u0084\3\2\2\2!\u0087\3\2\2\2#\u0089"+
		"\3\2\2\2%\u008b\3\2\2\2\'\u008d\3\2\2\2)\u008f\3\2\2\2+\u0093\3\2\2\2"+
		"-\u0097\3\2\2\2/\u009d\3\2\2\2\61\u00a2\3\2\2\2\63\u00a7\3\2\2\2\65\u00aa"+
		"\3\2\2\2\67\u00af\3\2\2\29\u00b4\3\2\2\2;\u00ba\3\2\2\2=\u00bf\3\2\2\2"+
		"?\u00c7\3\2\2\2A\u00cc\3\2\2\2C\u00d2\3\2\2\2E\u00d4\3\2\2\2G\u00d6\3"+
		"\2\2\2I\u00de\3\2\2\2K\u00fa\3\2\2\2M\u00fc\3\2\2\2O\u0105\3\2\2\2Q\u0107"+
		"\3\2\2\2S\u0111\3\2\2\2U\u0114\3\2\2\2W\u0125\3\2\2\2YZ\7.\2\2Z\4\3\2"+
		"\2\2[\\\7<\2\2\\\6\3\2\2\2]^\7=\2\2^\b\3\2\2\2_`\7v\2\2`a\7t\2\2ab\7w"+
		"\2\2bc\7g\2\2c\n\3\2\2\2de\7h\2\2ef\7c\2\2fg\7n\2\2gh\7u\2\2hi\7g\2\2"+
		"i\f\3\2\2\2jk\7?\2\2k\16\3\2\2\2lm\7?\2\2mn\7?\2\2n\20\3\2\2\2op\7#\2"+
		"\2pq\7?\2\2q\22\3\2\2\2rs\7@\2\2s\24\3\2\2\2tu\7@\2\2uv\7?\2\2v\26\3\2"+
		"\2\2wx\7>\2\2x\30\3\2\2\2yz\7>\2\2z{\7?\2\2{\32\3\2\2\2|}\7p\2\2}~\7q"+
		"\2\2~\177\7v\2\2\177\34\3\2\2\2\u0080\u0081\7c\2\2\u0081\u0082\7p\2\2"+
		"\u0082\u0083\7f\2\2\u0083\36\3\2\2\2\u0084\u0085\7q\2\2\u0085\u0086\7"+
		"t\2\2\u0086 \3\2\2\2\u0087\u0088\7-\2\2\u0088\"\3\2\2\2\u0089\u008a\7"+
		"/\2\2\u008a$\3\2\2\2\u008b\u008c\7,\2\2\u008c&\3\2\2\2\u008d\u008e\7\61"+
		"\2\2\u008e(\3\2\2\2\u008f\u0090\7x\2\2\u0090\u0091\7c\2\2\u0091\u0092"+
		"\7t\2\2\u0092*\3\2\2\2\u0093\u0094\7k\2\2\u0094\u0095\7p\2\2\u0095\u0096"+
		"\7v\2\2\u0096,\3\2\2\2\u0097\u0098\7h\2\2\u0098\u0099\7n\2\2\u0099\u009a"+
		"\7q\2\2\u009a\u009b\7c\2\2\u009b\u009c\7v\2\2\u009c.\3\2\2\2\u009d\u009e"+
		"\7e\2\2\u009e\u009f\7j\2\2\u009f\u00a0\7c\2\2\u00a0\u00a1\7t\2\2\u00a1"+
		"\60\3\2\2\2\u00a2\u00a3\7d\2\2\u00a3\u00a4\7q\2\2\u00a4\u00a5\7q\2\2\u00a5"+
		"\u00a6\7n\2\2\u00a6\62\3\2\2\2\u00a7\u00a8\7k\2\2\u00a8\u00a9\7h\2\2\u00a9"+
		"\64\3\2\2\2\u00aa\u00ab\7v\2\2\u00ab\u00ac\7j\2\2\u00ac\u00ad\7g\2\2\u00ad"+
		"\u00ae\7p\2\2\u00ae\66\3\2\2\2\u00af\u00b0\7g\2\2\u00b0\u00b1\7n\2\2\u00b1"+
		"\u00b2\7u\2\2\u00b2\u00b3\7g\2\2\u00b38\3\2\2\2\u00b4\u00b5\7g\2\2\u00b5"+
		"\u00b6\7p\2\2\u00b6\u00b7\7f\2\2\u00b7\u00b8\7k\2\2\u00b8\u00b9\7h\2\2"+
		"\u00b9:\3\2\2\2\u00ba\u00bb\7h\2\2\u00bb\u00bc\7w\2\2\u00bc\u00bd\7p\2"+
		"\2\u00bd\u00be\7e\2\2\u00be<\3\2\2\2\u00bf\u00c0\7g\2\2\u00c0\u00c1\7"+
		"p\2\2\u00c1\u00c2\7f\2\2\u00c2\u00c3\7h\2\2\u00c3\u00c4\7w\2\2\u00c4\u00c5"+
		"\7p\2\2\u00c5\u00c6\7e\2\2\u00c6>\3\2\2\2\u00c7\u00c8\7t\2\2\u00c8\u00c9"+
		"\7g\2\2\u00c9\u00ca\7c\2\2\u00ca\u00cb\7f\2\2\u00cb@\3\2\2\2\u00cc\u00cd"+
		"\7y\2\2\u00cd\u00ce\7t\2\2\u00ce\u00cf\7k\2\2\u00cf\u00d0\7v\2\2\u00d0"+
		"\u00d1\7g\2\2\u00d1B\3\2\2\2\u00d2\u00d3\7*\2\2\u00d3D\3\2\2\2\u00d4\u00d5"+
		"\7+\2\2\u00d5F\3\2\2\2\u00d6\u00da\t\2\2\2\u00d7\u00d9\t\3\2\2\u00d8\u00d7"+
		"\3\2\2\2\u00d9\u00dc\3\2\2\2\u00da\u00d8\3\2\2\2\u00da\u00db\3\2\2\2\u00db"+
		"H\3\2\2\2\u00dc\u00da\3\2\2\2\u00dd\u00df\4\62;\2\u00de\u00dd\3\2\2\2"+
		"\u00df\u00e0\3\2\2\2\u00e0\u00de\3\2\2\2\u00e0\u00e1\3\2\2\2\u00e1J\3"+
		"\2\2\2\u00e2\u00e4\4\62;\2\u00e3\u00e2\3\2\2\2\u00e4\u00e5\3\2\2\2\u00e5"+
		"\u00e3\3\2\2\2\u00e5\u00e6\3\2\2\2\u00e6\u00e7\3\2\2\2\u00e7\u00eb\7\60"+
		"\2\2\u00e8\u00ea\4\62;\2\u00e9\u00e8\3\2\2\2\u00ea\u00ed\3\2\2\2\u00eb"+
		"\u00e9\3\2\2\2\u00eb\u00ec\3\2\2\2\u00ec\u00fb\3\2\2\2\u00ed\u00eb\3\2"+
		"\2\2\u00ee\u00f0\4\62;\2\u00ef\u00ee\3\2\2\2\u00f0\u00f3\3\2\2\2\u00f1"+
		"\u00ef\3\2\2\2\u00f1\u00f2\3\2\2\2\u00f2\u00f4\3\2\2\2\u00f3\u00f1\3\2"+
		"\2\2\u00f4\u00f6\7\60\2\2\u00f5\u00f7\4\62;\2\u00f6\u00f5\3\2\2\2\u00f7"+
		"\u00f8\3\2\2\2\u00f8\u00f6\3\2\2\2\u00f8\u00f9\3\2\2\2\u00f9\u00fb\3\2"+
		"\2\2\u00fa\u00e3\3\2\2\2\u00fa\u00f1\3\2\2\2\u00fbL\3\2\2\2\u00fc\u00ff"+
		"\7)\2\2\u00fd\u0100\5S*\2\u00fe\u0100\n\4\2\2\u00ff\u00fd\3\2\2\2\u00ff"+
		"\u00fe\3\2\2\2\u00ff\u0100\3\2\2\2\u0100\u0101\3\2\2\2\u0101\u0102\7)"+
		"\2\2\u0102N\3\2\2\2\u0103\u0106\5\t\5\2\u0104\u0106\5\13\6\2\u0105\u0103"+
		"\3\2\2\2\u0105\u0104\3\2\2\2\u0106P\3\2\2\2\u0107\u010c\7$\2\2\u0108\u010b"+
		"\5S*\2\u0109\u010b\n\4\2\2\u010a\u0108\3\2\2\2\u010a\u0109\3\2\2\2\u010b"+
		"\u010e\3\2\2\2\u010c\u010a\3\2\2\2\u010c\u010d\3\2\2\2\u010d\u010f\3\2"+
		"\2\2\u010e\u010c\3\2\2\2\u010f\u0110\7$\2\2\u0110R\3\2\2\2\u0111\u0112"+
		"\7^\2\2\u0112\u0113\t\5\2\2\u0113T\3\2\2\2\u0114\u0115\7\61\2\2\u0115"+
		"\u0116\7\61\2\2\u0116\u011a\3\2\2\2\u0117\u0119\n\6\2\2\u0118\u0117\3"+
		"\2\2\2\u0119\u011c\3\2\2\2\u011a\u0118\3\2\2\2\u011a\u011b\3\2\2\2\u011b"+
		"\u011e\3\2\2\2\u011c\u011a\3\2\2\2\u011d\u011f\7\17\2\2\u011e\u011d\3"+
		"\2\2\2\u011e\u011f\3\2\2\2\u011f\u0120\3\2\2\2\u0120\u0121\7\f\2\2\u0121"+
		"\u0122\3\2\2\2\u0122\u0123\b+\2\2\u0123V\3\2\2\2\u0124\u0126\t\7\2\2\u0125"+
		"\u0124\3\2\2\2\u0126\u0127\3\2\2\2\u0127\u0125\3\2\2\2\u0127\u0128\3\2"+
		"\2\2\u0128\u0129\3\2\2\2\u0129\u012a\b,\2\2\u012aX\3\2\2\2\21\2\u00da"+
		"\u00e0\u00e5\u00eb\u00f1\u00f8\u00fa\u00ff\u0105\u010a\u010c\u011a\u011e"+
		"\u0127\3\b\2\2";
	public static final ATN _ATN =
		new ATNDeserializer().deserialize(_serializedATN.toCharArray());
	static {
		_decisionToDFA = new DFA[_ATN.getNumberOfDecisions()];
		for (int i = 0; i < _ATN.getNumberOfDecisions(); i++) {
			_decisionToDFA[i] = new DFA(_ATN.getDecisionState(i), i);
		}
	}
}