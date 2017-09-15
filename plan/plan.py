from coplen import Course, Goals, Month, Reference, Topic, generate

if __name__ == '__main__':
    course = Course(
            kind='minicurso',
            title='Minicurso de Desenvolvimento para Game Boy Advance',
            hours={
                'theoretical': 10,
                'practice': 8,
                },
            start=Month.SEPTEMBER,
            end=Month.NOVEMBER,
            year=2017,
            targets=[
                'Ciência da Computação',
                'Interessados em computação embarcada',
                ],
            requires=[
                'Mínimo conhecimento a respeito de programação'
                ' imperativa (variáveis, funções, estruturas'
                ' condicionais/de repetição, ...) e circuitos'
                ' (o que é um registrador, sinais de entrada/'
                'saída, ...)',
                ],
            goals=Goals(
                general='Entusiasmar alunos de graduação a respeito'
                        ' de sistemas embarcados, mídia e otimizações'
                        ' de baixo nível, mostrando uma aplicação'
                        ' diferente do habitual e apresentando o'
                        ' funcionamento e interação do Hardware'
                        ' \\textit{Hardware} envolvido',
                specific=[
                    'Apresentar as especificações técnicas da plataforma',

                    'Mencionar as limitações da plataforma dentro do seu '
                    ' contexto histórico',

                    'Apresentar a interação entre os registradores de'
                    ' controle e suas respectivas funcionalidades a nível'
                    ' de \\textit{Hardware}',

                    'Apresentar o funcionamento de mídia analógica/'
                    'digital',

                    'Apresentar otimizações válidas para sistemas'
                    ' embarcados, bem como tecnologias envolvidas nos'
                    ' mais modernos',

                    'Prover pleno entendimento da integração entre'
                    ' programação de alto-nível e o \\textit{Hardware}',

                    'Apresentar paralelos entre a tecnologia ensinada e as'
                    ' atualmente utilizadas',

                    'Apresentar o uso de C++ moderno em sistemas'
                    ' embarcados, bem como suas vantagens e desvantagens',
                    ],
                ),
            topics=[
                Topic(
                    title='Introdução ao GBA',
                    duration=2,
                    items=[
                        'Histórico de limitação dos consoles pré-2000',
                        'Especificações técnicas do GBA',
                        'Mapeamento de memória do GBA',
                        'VRAM',
                        'Assembly Thumb',
                        '\\textit{Mode 3}',
                        'Introdução a C++',
                    ],
                ),
                Topic(
                    title='Modos de Visor Bitmapeados',
                    duration=2,
                    items=[
                        'Visão geral de Modos Bitmapeados',
                        'PPU (\\textit{Pixel Processing Unit})',
                        'Análise da Performance do \\textit{Mode 3}',
                        '\\textit{V-Sync}',
                        '\\textit{Mode 5}',
                        '\\textit{Page-Flipping}',
                        '\\textit{Mode 4}',
                        '\\textit{Paletting}',
                        '\\textit{Endianness}',
                    ],
                ),
                Topic(
                    title='Objetos de jogo e \\textit{Input}',
                    duration=2,
                    items=[
                        'Leitura do \\textit{Keypad}',
                        '\\textit{Sprites}',
                        'OAM (\\textit{Object Attribute Memory})',
                        'Múltiplos objetos',
                        'Introdução a arquivos de \\textit{Bitmap}',
                    ],
                ),
                Topic(
                    title='Arquivos \\textit{Bitmap}',
                    duration=2,
                    items=[
                        '\\textit{std::ifstream} e \\textit{std::ofstream}',
                        'Header de tipo de arquivo',
                        'Header BMP',
                    ],
                ),
                Topic(
                    title='Modos de Visor em Caractere',
                    duration=2,
                    items=[
                        '\\textit{Tilemapping}',
                        '\\textit{Palette-Swapping}',
                    ],
                ),
                Topic(
                    title='Funcionalidades e Efeitos Gráficos',
                    duration=2,
                    items=[
                        '\\textit{Windowing}',
                        '\\textit{Alpha-Blend}',
                        'Luminosidade',
                        'Efeito mosáico',
                        'Matriz de transformação',
                    ],
                ),
                Topic(
                    title='Texto, Economia de energia e Cartucho',
                    duration=2,
                    items=[
                        'Fontes',
                        'Janelas de diálogo',
                        '\\textit{Hardware-Interrupts}',
                        'DMA - \\textit{Dynamic Memory Access}',
                        '\\textit{SaveRAM}',
                    ],
                ),
                Topic(
                    title='Áudio',
                    duration=2,
                    items=[
                        'Arquivos MIDI',
                        'Ondas sonoras',
                        'Interferência construtiva/destrutiva',
                        '\\textit{BIOS-Calls} para áudio',
                        'Efeitos sonoros (SFX) e arquivos WAV',
                    ],
                ),
                Topic(
                    title='Construção de um jogo',
                    duration=2,
                    items=[
                        '\\textit{Splash Screen}',
                        'Eventos e animações',
                        'Gerência de memória para sistemas embarcados',
                        'Boas práticas de desenvolvimento',
                    ],
                ),
            ],
            references=[
                Reference(
                    symbol='conarac',
                    author = "J. Vijn",
                    title = "{TONC}",
                    url = "http://www.coranac.com/tonc/",
                    note = "\\url{http://www.coranac.com/tonc/}",
                ),

                Reference(
                    symbol='gbatek',
                    author = "Martin Korth",
                    title = "{GBATEK - GBA/NDS Technical Info}",
                    url = "http://problemkaputt.de/gbatek.htm",
                    note = "\\url{http://problemkaputt.de/gbatek.htm}",
                ),

                Reference(
                    symbol='gbadev-org',
                    author = "GBADEV.org",
                    title = "{Gameboy Advance Development}",
                    url = "http://www.gbadev.org/docs.php",
                    note = "\\url{http://www.gbadev.org/docs.php}",
                ),

                Reference(
                    symbol='wikipedia:gba',
                    author = "Wikipedia",
                    title = "{Game Boy Advance}",
                    url = "https://en.wikipedia.org/wiki/Game_Boy_Advance",
                    note = "\\url{https://en.wikipedia.org/wiki/Game_Boy_Advance}",
                ),

                Reference(
                    symbol='assemblergames',
                    author = "Arcade",
                    title = "{Game Boy Advance Schematic (Cadsoft Eagle Files)}",
                    url = "http://assemblergames.com/l/threads/game-boy-advance-schematic-cadsoft-eagle-files.54814/",
                    note = "\\url{http://assemblergames.com/l/threads/game-boy-advance-schematic-cadsoft-eagle-files.54814/}",
                ),

                Reference(
                    symbol='armisa',
                    author = "ARM University Program",
                    title = "{The ARM Instruction Set}",
                    url = "http://simplemachines.it/doc/arm_inst.pdf",
                    note = "\\url{http://simplemachines.it/doc/arm_inst.pdf}",
                ),

                Reference(
                    symbol='arminfocenter',
                    author = "ARM",
                    title = "{ARM Information Center}",
                    url = "http://infocenter.arm.com/help/index.jsp?topic=/com.arm.doc.dui0497a/BABJGHFJ.html",
                    note = "\\url{http://infocenter.arm.com/help/index.jsp?topic=/com.arm.doc.dui0497a/BABJGHFJ.html}",
                ),

                Reference(
                    symbol='mark:armisa',
                    author = "Mark McDermott",
                    title = "{The ARM Instruction Set Architecture}",
                    url = "http://users.ece.utexas.edu/~valvano/EE345M/Arm_EE382N_4.pdf",
                    note = "\\url{http://users.ece.utexas.edu/~valvano/EE345M/Arm_EE382N_4.pdf}",
                ),
            ]
        )

    generate(course, output='plan.tex')
