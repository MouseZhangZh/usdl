# USDL

[![CMake on multiple platforms](https://github.com/MouseZhangZh/usdl/actions/workflows/cmake-multi-platform.yml/badge.svg)](https://github.com/MouseZhangZh/usdl/actions/workflows/cmake-multi-platform.yml)
[![CodeQL](https://github.com/MouseZhangZh/usdl/actions/workflows/codeql.yml/badge.svg)](https://github.com/MouseZhangZh/usdl/actions/workflows/codeql.yml)

## Introduction

USDL is universal simple data language, which is designed to be easy to parse and easy to use.

## Syntax

USDL's syntax is very simple, it's just a list of key-value pairs, like this:

```
{
    <key1> = 123.456 ;
    <key2> = "string" ;
    <key3> = [1, 2, 3, [4, 5, 6]] ;
    <key4> = {
        <key5> = 123 ;
        <key6> = "string" ;
    } ;
}
```