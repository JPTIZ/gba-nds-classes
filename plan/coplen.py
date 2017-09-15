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
    kind: str
    title: str
    hours: Dict[str, int]
    start: Month
    end: Month
    year: int
    targets: List[str]
    requires: List[str]
    goals: Goals
    topics: List[Topic]
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


def lookahead(iterable):
    it = iter(iterable)
    prev = next(it)
    for val in it:
        yield prev, True
        prev = val
    yield prev, False


def save(text, output):
    with open(output, 'w') as f:
        f.write(text)


def generate(course, lang=default_lang, sketch: str ='sketch.tex', output: str = 'output.tex'):

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
    latex_env.filters['lookahead'] = lookahead

    print('Generating TeX...')
    template = latex_env.get_template('sketch.tex')
    save(template.render(course=course, lang=lang), output)
