(S'b66a940cace195193e138126bc0fd433'
p1
(ihappydoclib.parseinfo.moduleinfo
ModuleInfo
p2
(dp3
S'_namespaces'
p4
((dp5
S'DictWrapper'
p6
(ihappydoclib.parseinfo.classinfo
ClassInfo
p7
(dp8
g4
((dp9
(dp10
S'__hash__'
p11
(ihappydoclib.parseinfo.functioninfo
FunctionInfo
p12
(dp13
g4
((dp14
(dp15
tp16
sS'_exception_info'
p17
(dp18
sS'_parameter_names'
p19
(S'self'
p20
tp21
sS'_parameter_info'
p22
(dp23
g20
(NNNtp24
ssS'_filename'
p25
S'../python/frowns/mdl_parsers/Generator.py'
p26
sS'_docstring'
p27
S''
sS'_name'
p28
g11
sS'_parent'
p29
g7
sS'_comment_info'
p30
(dp31
(S'IndexGenerator'
tp32
S' this simply allows a dictionary to be\n  hased\n'
p33
s(S'Generator'
tp34
S" \n The generator has callbacks for the following events\n  'atom' -> adds an atom\n  'bonds' -> adds a bond\n  'branch_out' -> pushes a branch\n  'branch_in' -> ends the last branch\n  'closure' -> adds a closure or completes a closure\n  'dot' -> a special case of a blank (empty) bond\n \n Implementation Notes\n  lastAtom = None\n  lastBond = None\n  closures = {}\n  when an atom is added\n    if there is no lastAtom then do nothing.\n    else create a blank lastBond if none exists\n         use lastBond to connect atom to lastAtom\n    update lastAtom to be the new atom\n    clear lastBond because it has been used\n \n  when a bond is added\n    make sure that lastBond is None otherwise\n    there are two bonds in a row\n \n  branch_out\n    there is a branch stack which stores the current\n    lastAtom state\n \n  branch_in\n    go back to the last branch stack state thus\n    closing the branch\n \n  closure\n    a closure maps an atom to a closure index\n    when the closure index is seen again the current\n    atom is bonded to the closure atom.\n \n    XXX FIX ME\n     Daylight adds the bond to the molecule when the\n     closure index first appears.\n \n     This code adds the bond when the closure is completed.\n     So bonds will not be in the same order as daylight.\n"
p35
ssS'_configuration_values'
p36
(dp37
sS'_class_info'
p38
g14
sS'_function_info'
p39
g15
sS'_comments'
p40
S''
sbsS'__str__'
p41
(ihappydoclib.parseinfo.functioninfo
FunctionInfo
p42
(dp43
g4
((dp44
(dp45
tp46
sg17
(dp47
sg19
(S'self'
p48
tp49
sg22
(dp50
g48
(NNNtp51
ssg25
g26
sg27
S''
sg28
g41
sg29
g7
sg30
g31
sg36
(dp52
sg38
g44
sg39
g45
sg40
S''
sbsS'__repr__'
p53
(ihappydoclib.parseinfo.functioninfo
FunctionInfo
p54
(dp55
g4
((dp56
(dp57
tp58
sg17
(dp59
sg19
(S'self'
p60
tp61
sg22
(dp62
g60
(NNNtp63
ssg25
g26
sg27
S''
sg28
g53
sg29
g7
sg30
g31
sg36
(dp64
sg38
g56
sg39
g57
sg40
S''
sbsS'__init__'
p65
(ihappydoclib.parseinfo.functioninfo
FunctionInfo
p66
(dp67
g4
((dp68
(dp69
tp70
sg17
(dp71
sg19
(S'self'
p72
S'data'
p73
S'idGenerator'
p74
tp75
sg22
(dp76
g72
(NNNtp77
sg73
(NNNtp78
sg74
(I1
S'IndexGenerator()'
Ntp79
ssg25
g26
sg27
S''
sg28
g65
sg29
g7
sg30
g31
sg36
(dp80
sg38
g68
sg39
g69
sg40
S''
sbsS'__cmp__'
p81
(ihappydoclib.parseinfo.functioninfo
FunctionInfo
p82
(dp83
g4
((dp84
(dp85
tp86
sg17
(dp87
sg19
(S'self'
p88
S'other'
p89
tp90
sg22
(dp91
g88
(NNNtp92
sg89
(NNNtp93
ssg25
g26
sg27
S''
sg28
g81
sg29
g7
sg30
g31
sg36
(dp94
sg38
g84
sg39
g85
sg40
S''
sbstp95
sg25
g26
sg27
S''
sS'_class_member_info'
p96
(lp97
sg28
g6
sg29
g2
sg30
g31
sS'_base_class_info'
p98
(lp99
sg36
(dp100
sg38
g9
sg39
g10
sg40
S''
sbsS'IndexGenerator'
p101
(ihappydoclib.parseinfo.classinfo
ClassInfo
p102
(dp103
g4
((dp104
(dp105
S'__init__'
p106
(ihappydoclib.parseinfo.functioninfo
FunctionInfo
p107
(dp108
g4
((dp109
(dp110
tp111
sg17
(dp112
sg19
(S'self'
p113
S'start'
p114
tp115
sg22
(dp116
g114
(I1
S'0'
Ntp117
sg113
(NNNtp118
ssg25
g26
sg27
S''
sg28
g106
sg29
g102
sg30
g31
sg36
(dp119
sg38
g109
sg39
g110
sg40
S''
sbsS'next'
p120
(ihappydoclib.parseinfo.functioninfo
FunctionInfo
p121
(dp122
g4
((dp123
(dp124
tp125
sg17
(dp126
sg19
(S'self'
p127
tp128
sg22
(dp129
g127
(NNNtp130
ssg25
g26
sg27
S''
sg28
g120
sg29
g102
sg30
g31
sg36
(dp131
sg38
g123
sg39
g124
sg40
S''
sbstp132
sg25
g26
sg27
S''
sg96
(lp133
sg28
g101
sg29
g2
sg30
g31
sg98
(lp134
sg36
(dp135
sg38
g104
sg39
g105
sg40
g33
sbsS'Generator'
p136
(ihappydoclib.parseinfo.classinfo
ClassInfo
p137
(dp138
g4
((dp139
(dp140
S'addState'
p141
(ihappydoclib.parseinfo.functioninfo
FunctionInfo
p142
(dp143
g4
((dp144
(dp145
tp146
sg17
(dp147
sg19
(S'self'
p148
S'state'
p149
S'data'
p150
tp151
sg22
(dp152
g148
(NNNtp153
sg150
(NNNtp154
sg149
(NNNtp155
ssg25
g26
sg27
S''
sg28
g141
sg29
g137
sg30
g31
sg36
(dp156
sg38
g144
sg39
g145
sg40
S''
sbsS'addBond'
p157
(ihappydoclib.parseinfo.functioninfo
FunctionInfo
p158
(dp159
g4
((dp160
(dp161
tp162
sg17
(dp163
sg19
(S'self'
p164
S'bond'
p165
tp166
sg22
(dp167
g164
(NNNtp168
sg165
(NNNtp169
ssg25
g26
sg27
S''
sg28
g157
sg29
g137
sg30
g31
sg36
(dp170
sg38
g160
sg39
g161
sg40
S''
sbsS'addClosure'
p171
(ihappydoclib.parseinfo.functioninfo
FunctionInfo
p172
(dp173
g4
((dp174
(dp175
tp176
sg17
(dp177
S'"Closure specified with two different bond types %s!=%s" %( closureBond, self.lastBond )'
p178
Nssg19
(S'self'
p179
S'closure'
p180
tp181
sg22
(dp182
g180
(NNNtp183
sg179
(NNNtp184
ssg25
g26
sg27
S'(closure) -> add a closure'
p185
sg28
g171
sg29
g137
sg30
g31
sg36
(dp186
sg38
g174
sg39
g175
sg40
S''
sbsS'addAtom'
p187
(ihappydoclib.parseinfo.functioninfo
FunctionInfo
p188
(dp189
g4
((dp190
(dp191
tp192
sg17
(dp193
sg19
(S'self'
p194
S'atom'
p195
tp196
sg22
(dp197
g194
(NNNtp198
sg195
(NNNtp199
ssg25
g26
sg27
S'(atom)->add atom to the atom stack\n        combine with lastBond if one exists and set lastBond\n        to None since it has been used'
p200
sg28
g187
sg29
g137
sg30
g31
sg36
(dp201
sg38
g190
sg39
g191
sg40
S''
sbsS'popBranch'
p202
(ihappydoclib.parseinfo.functioninfo
FunctionInfo
p203
(dp204
g4
((dp205
(dp206
tp207
sg17
(dp208
S'"Illegal bond before branch end"'
p209
NsS'"Unbalanced branch"'
p210
Nssg19
(S'self'
p211
S'data'
p212
tp213
sg22
(dp214
g211
(NNNtp215
sg212
(NNNtp216
ssg25
g26
sg27
S''
sg28
g202
sg29
g137
sg30
g31
sg36
(dp217
sg38
g205
sg39
g206
sg40
S''
sbsS'pushBranch'
p218
(ihappydoclib.parseinfo.functioninfo
FunctionInfo
p219
(dp220
g4
((dp221
(dp222
tp223
sg17
(dp224
sg19
(S'self'
p225
S'data'
p226
tp227
sg22
(dp228
g225
(NNNtp229
sg226
(NNNtp230
ssg25
g26
sg27
S''
sg28
g218
sg29
g137
sg30
g31
sg36
(dp231
sg38
g221
sg39
g222
sg40
S''
sbsS'mol'
p232
(ihappydoclib.parseinfo.functioninfo
FunctionInfo
p233
(dp234
g4
((dp235
(dp236
tp237
sg17
(dp238
S'"Closure not completed %s" %(self.closures.keys() [ 0 ] )'
p239
Nssg19
(S'self'
p240
tp241
sg22
(dp242
g240
(NNNtp243
ssg25
g26
sg27
S''
sg28
g232
sg29
g137
sg30
g31
sg36
(dp244
sg38
g235
sg39
g236
sg40
S''
sbsS'clearLastBond'
p245
(ihappydoclib.parseinfo.functioninfo
FunctionInfo
p246
(dp247
g4
((dp248
(dp249
tp250
sg17
(dp251
S'"Syntax Error . follows bond"'
p252
Nssg19
(S'self'
p253
S'data'
p254
tp255
sg22
(dp256
g253
(NNNtp257
sg254
(NNNtp258
ssg25
g26
sg27
S''
sg28
g245
sg29
g137
sg30
g31
sg36
(dp259
sg38
g248
sg39
g249
sg40
S''
sbsS'__init__'
p260
(ihappydoclib.parseinfo.functioninfo
FunctionInfo
p261
(dp262
g4
((dp263
(dp264
tp265
sg17
(dp266
sg19
(S'self'
p267
S'Atom'
p268
S'Bond'
p269
S'Molecule'
p270
tp271
sg22
(dp272
g267
(NNNtp273
sg269
(I1
S'Bond'
Ntp274
sg270
(I1
S'Molecule'
Ntp275
sg268
(I1
S'Atom'
Ntp276
ssg25
g26
sg27
S''
sg28
g260
sg29
g137
sg30
g31
sg36
(dp277
sg38
g263
sg39
g264
sg40
S''
sbstp278
sg25
g26
sg27
S''
sg96
(lp279
sg28
g136
sg29
g2
sg30
g31
sg98
(lp280
sg36
(dp281
sg38
g139
sg39
g140
sg40
g35
sbs(dp282
S'clearDict'
p283
(ihappydoclib.parseinfo.functioninfo
FunctionInfo
p284
(dp285
g4
((dp286
(dp287
tp288
sg17
(dp289
sg19
(S'dict'
p290
tp291
sg22
(dp292
g290
(NNNtp293
ssg25
g26
sg27
S''
sg28
g283
sg29
g2
sg30
g31
sg36
(dp294
sg38
g286
sg39
g287
sg40
S''
sbstp295
sS'_import_info'
p296
(ihappydoclib.parseinfo.imports
ImportInfo
p297
(dp298
S'_named_imports'
p299
(dp300
S'frowns.Molecule'
p301
(lp302
S'Molecule'
p303
asS'frowns.Atom'
p304
(lp305
S'Atom'
p306
asS'frowns.Objects.ObjectGenerator'
p307
(lp308
S'parse_atom'
p309
aS'parse_bond'
p310
asS'frowns.Bond'
p311
(lp312
S'Bond'
p313
assS'_straight_imports'
p314
(lp315
sbsg25
g26
sg27
S'"""Generator\n\n Generator is a class that is used for reading linearized graph notations\n examples of linearized graph notations are smiles (http://www.daylight.com)\n although Tripos has one as well (http://www.tripos.com)\n\n A linearized notation consists of these parts:\n\n  1 atoms\n  2 bonds\n  3 branches - specified by ( and ) in smiles\n  4 closures - specifed by numbers or %12 in smiles\n\n A generator conforms to the following interface\n\n class Generator:\n   def __init__(self):\n      ...\n   def addEvent(self, event, data):\n       \'\'\'(event, data) -> add event with event data \'data\' to\n       the generator.\n\n       the event and forms of the data are given from the\n       description of the parsing routine\'\'\'\n\n   def mol(self):\n       \'\'\'-> return the generated molecule\'\'\'\n"""'
p316
sg28
S'Generator'
p317
sg29
Nsg30
g31
sg36
(dp318
S'include_comments'
p319
I1
sS'cacheFilePrefix'
p320
S'.happydoc.'
p321
sS'useCache'
p322
I1
sS'docStringFormat'
p323
S'StructuredText'
p324
ssg38
g5
sg39
g282
sg40
S''
sbt.