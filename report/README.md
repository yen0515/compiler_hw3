# hw3 report

|||
|-:|:-|
|Name|黃彥慈|
|ID|0716088|

## How much time did you spend on this project

50 hours.  

## Project overview

改動主要可以分成幾種不同的類型，分別是對scanner.l parser.y 與其他.cpp.hpp檔案的改動  
### 對scanner.l的改動  
對scanner.l的改動主要是針對有些terminal在建AST時需要獲取其相對應的值來進行建立的作業。  
1. ID跟string的type都是string，因此對應到union中的char* 也就是identifier，所以將兩者的yytext轉為string之後存給yylval.identifier。  
2. integer跟octal_integer皆為integer，因此對應到union中的valurInt，所以將兩者的yytext轉為integer之後存給yylval.valueInt。  
3. float和科學記號則都是float，因此對應到union中的valurFloat，所以將兩者的yytext轉為float之後存給yylval.valueFloat。  
### 對.hpp的改動  
由於.hpp中的改動大多相同，因此只取較為特殊的說明，而共同的為print()以及visitChildNode()，前者負責將node裡面對應的資訊print出來，後者則是負責觸發該node的childnode中的print()，詳細作法則見下點。  
1. ast.hpp中，首先我先分別將AstNode* 跟vector<AstNode*>分別typedef為Node與Nodevec以方便之後進行宣告；再來定義4個enum，第一個enumoperator分別代表了所有不同的operator，以方便之後來判斷接收到的為何種operator，第二個enumTypeSet則負責判斷接收到的是一個scalar、array、const或是UNKNOWN，第三個enumType則負責辨別接收到的是哪一種type，為int或是boolean等等，而若TypeSet判定為UNKNOWN時便代表其type為void，若為array則代表其type為UNKNOWN，最後一個enum則是負責分辨接收到的boolean為true或是false。  
再來則是兩個struct，分別是variableinfo與nodewithtypelist，前者負責儲存一個variable的TypeSet、Type、若其為array時則array值會是多少的vector與int、float、string與boolean4種type的儲存值，因此便可以透過判斷該變數所儲存的TypeSet與Type來判斷要取出的是其中哪一個值；後者則負責儲存function相關的值，node負責存宣告function時的declaration，type負責儲存其性質相關的資料，counter則負責儲存該argument list中總共有多少個argument；最後則是在class內宣告的一個public變數spacecounter，負責計算該node在要print出相關資料時前方需要空幾個空白。  
2. 再來是UnaryOperator.hpp與BinaryOperator.hpp，除了上述提到的兩個function之外，getop()負責透過wnumoperator來判斷接收到的operator為哪一種並return相對應的string type operator。  
3. 接下來是CostantValue.hpp中的getval()，負責透過判斷TypeSet與Type來得到該constant為何，並且return該值的string type。  
4. 再來是function.hpp中的get_returntype()與get_argtype()，顧名思義便是要透過判斷前述的nodewithtypelist中的type中的TypeSet與Type來得到其argument type與透過其constructor傳入的Variableinfo的TypeSet跟Type來判斷其return type。  
5. 最後則是variable.hpp中的gettype()，與前述的類似，便是透過其constructor傳入的Variableinfo的TypeSet跟Type來判斷其ㄒvariable type。  
### 對.cpp的改動  
由於.cpp中的改動大多相同，且如getop()等單純判斷並return其相對應的值這類型的function也不多贅述，而共同的為print()以及visitChildNode()，前者先透過其spacecounter來預先print出空格，之後再根據要求print出所需要的資料，後者則是在判斷該childnode不為nullptr之後，先調整好該childnode的spacecounter之後觸發該childnode的print()。  
### 對parser.y的改動  
首先先將所有的.hpp include進來，並同時將所有.hpp給放進%code require，除了union內先便有的char* type外，另外新增了9種不同的type來提供下方的terminal與nonterminal使用，而nonterminal必定需要宣告其type，terminal則只要宣告需要取其值得即可，如operator或是INT_LITERAL等等，以上便是事前預備，底下便會根據不同CFG順序來進行說明。  
1. 將root定義為一ProgramNode之後，傳入其location、Program name與三個childnode。  
2. 不需新增action。  
3. 若會induce為Epsilon則將其值設為nullptr，否則便是承接其值。  
4. 若只會Induce出單一個nonterminal的話便是將$$ new成一Nodevec()後將該型態為Node的nonterminal的資訊push_back()進去；若會induce出兩個的話由於$$跟$1是相同的，因此將$1->push_back($2)後更新$$=$1即可。 
5. 與3.同理  
6. 與4.同理  
7. function可以為兩種型態，因此分別將各個型態的值存給$$即可。  
8. 先處理function declaration，首先先判斷其FormalArgList是否為空，若為空則不用做任何事，但若不為空則需取出其內部所有的值assign給一variableinfo之後push_back進arg_list，最後則是將成一個FunctionNode，並將其location、functionname與所有的childnode傳入constructor，而有一是因為沒有compound statement，因此便傳入nullptr。  
9. 與上述相同，唯一不同的僅是傳入constructor的不再是nullptr而是compound statement。  
10. 不需新增action。  
11. 與3.同理  
12. 與4.同理  
13. 將$$ new成一個nodewuthtypelist之後其type便是$3，counter則從0開始數，其餘的則是從IdList中一個個定義其type_set等性質後push_back進入一Nodevec，$$中的node則定義為一declaration node，由其location與剛剛的Nodevec所組成。  
14. 與4.同理   
15. 若為Epsilon則代表該function的return type為void，因此將$$ new成一個variableinfo後將其type_set設定為UNKNOWN、type設定為VOID，若不為Epsilon則同樣將$$ new成一個variableinfo後其type_set與type則皆與ScalarType也就是$2相同。  
16. 分為將變數宣告為type或是宣告為const兩種類型，若是宣告為type的話則設定一個Nodevec後將IdList中的所有資訊一個個拿出來後push_back進去，之後將$$ new成一DeclNode，其constructor由location與該Nodevec組成；若是宣告為constant則先將IdList中的資訊一一取出後存入一個個ConstantNode中，之後再將這些資訊push_back進一Nodevec並將$$ new成一DeclNode，其constructor由location與該Nodevec組成。  
17. 便是直接將值傳入。  
18. 將$$ new成一variableinfo之後根據其接收到的為哪一種type來決定其$$的type_set與type。  
19. 將$$ new成一variableinfo之後設定其type_set為array、type等同於scalar type、array_val則為$1傳入的資訊。  
20. 將$$ new成一variableinfo之後設定其type_set為array、type為UNKNOWN，並將$2也就是INT_LITERAL的值存入array_val中，或是將INT_LITERAL的值存入array_val中之後再更新$$的值為$1。  
21. 將$$ new成一variableinfo之後設定其type_set、type為相對應的值後，判斷NegOrNot的值來決定其值需不需要乘上負號。  
22. 若偵測到有負號時則將$$設為"-"來提供上述判定，否則即為nullptr。  
23. 將$$ new成一variableinfo之後設定其type_set、type、lit為相對應的值。  
24. 將$$ new成一variableinfo之後設定其type_set、type、lit為相對應的值。  
25. 將各類型statement的值皆傳給$$。  
26. 將compound statement new為一個CompoundStatementNode，其constructor則由其location與childnode組成。  
27. Simple分為3種，則根據其相對應的種類來new成不同的node並賦予其constructor需要的childnode值。  
28. 即new 成一個VariableReferenceNode，其constructor則由其location與childnode組成。 
29. 與3.同理  
30. 與4.同理  
31. 根據其相對應的type將$$ new成相對應的node並根據其要output的資訊來賦予其childnode  
32. 若condition有compound statement則將其賦予給$$，否則便為nullptr。  
33. 根據其相對應的type將$$ new成相對應的node並根據其要output的資訊來賦予其childnode  
34. 根據其相對應的type將$$ new成相對應的node並根據其要output的資訊來賦予其childnode  
35. 根據其相對應的type將$$ new成相對應的node並根據其要output的資訊來賦予其childnode  
36. 根據其相對應的type將$$ new成相對應的node並根據其要output的資訊來賦予其childnode  
37. 根據其相對應的type將$$ new成相對應的node並根據其要output的資訊來賦予其childnode  
38. 與3.同理  
39. 與4.同理  
40. 與3.同理  
41. 與4.同理  
42. 根據不同的或是constant new成相對應類型的node並賦予其值。  
  
## What is the hardest you think in this project

首先是對這份作業的了解，我大概花了4-5個小時來理解這些.cpp.hpp與.l.y之間的關係，也花費了不少時間來明白我該從哪裡開始下手與如何下手。  
再來則是作法的摸索，最一開始我沒有想到可以利用struct與enum來存取各個不同型態的node，耶因此花費許多時間在建立class內的元素與function上，也因此當我寫到測資2的時候便發現我寫的方法或許真的可行但是會十分麻煩且難懂，因此我完全換一種新的寫法，在與朋友討論之下便得出了現在這個寫法的雛形，但也因此白白浪費了許多時間。  
最後則是測資9，在for loop的最後要得到的string constant value包含了一個\n，因此我原先使用的std::printf()的寫法便會出問題，並且後來發現在scanner.l內，不可以使用strndup來存取yylval.identifier否則會出錯，改用strdup之後問題便迎刃而解。

## Feedback to T.A.s

如上述所說，由於我在scanner.l string值的回傳是直接複製助教原先在ID便寫上的strndup，因此後來出現問題後會需要一段時間後才能發現問題出在這裡。
