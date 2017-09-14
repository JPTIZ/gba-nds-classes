'''Course plan generator library.'''
from enum import Enum
from jinja2 import Template, Environment, FileSystemLoader
from os.path import abspath
from typing import NamedTuple, List, Dict, Tuple

class Month(Enum):
    '''Year's month.'''
    JANUARY = 1
    FEBRUARY = 2
    MARCH = 3
    APRIL = 4
    MAY = 5
    JUNE = 6
    JULY = 7
    AUGUST = 8
    SEPTEMBER = 9
    OCTOBER = 10
    NOVEMBER = 11
    DECEMBER = 12

class Topic(NamedTuple):
    '''Represents a single topic from the course plan.'''
    title: str
    duration: int
    items: List[str]
    extra_items: List[str] = []

class Reference(NamedTuple):
    '''A LaTeX reference entry.'''
    symbol: str
    author: str
    title: str
    url: str = ''
    note: str = ''

class Goals(NamedTuple):
    '''Course general and specific goals.'''
    general: str
    specific: List[str]

class Course(NamedTuple):
    '''A full course plan definition.'''
    kind: str  # = 'Minicurso'
    title: str # = 'Minicurso de Java'
    hours: Dict[str, int] # = {'theoretical': 10, 'practice': 8}
    start: Month
    end: Month
    year: int
    target: List[str]
    requires: List[str]
    goals: Goals
    topics: Dict[str, Topic]
    references: List[Reference]

default_lang = {
    Month.JANUARY: 'Janeiro',
    Month.FEBRUARY: 'Fevereiro',
    Month.MARCH: 'Março',
    Month.APRIL: 'Abril',
    Month.MAY: 'Maio',
    Month.JUNE: 'Junho',
    Month.JULY: 'Julho',
    Month.AUGUST: 'Agosto',
    Month.SEPTEMBER: 'Setembro',
    Month.OCTOBER: 'Outubro',
    Month.NOVEMBER: 'Novembro',
    Month.DECEMBER: 'Dezembro',
}

def generate(course, lang=default_lang, sketch: str ='sketch.tex'):#: Course):

    latex_env = Environment(
                    block_start_string = '\BLOCK{',
                    block_end_string = '}',
                    variable_start_string = '\VAR{',
                    variable_end_string = '}',
                    comment_start_string = '\#{',
                    comment_end_string = '}',
                    line_statement_prefix = '%%',
                    line_comment_prefix = '%#',
                    trim_blocks = True,
                    autoescape = False,
                    loader = FileSystemLoader(abspath('.'))
                )

    print('Generating TeX...')
    template = latex_env.get_template('sketch.tex')
    print(template.render(course=course, lang=lang))
