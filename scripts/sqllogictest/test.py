from typing import List
from .base_statement import BaseStatement


class SQLLogicTest:
    __slots__ = ['path', 'statements', 'skipped']

    def __init__(self, path: str):
        self.path: str = path
        self.statements: List[BaseStatement] = []
        self.skipped = False

    def add_statement(self, statement: BaseStatement):
        self.statements.append(statement)

    def is_sqlite_test(self):
        return 'test/sqlite/select' in self.path or 'third_party/sqllogictest' in self.path

    def skip(self, val):
        self.skipped = val
