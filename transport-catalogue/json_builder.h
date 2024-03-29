#pragma once

#include "json.h"

namespace json {

    class Builder;
    class DictItemContext;
    class KeyItemContext;
    class ArrayItemContext;

    class BaseContext {
    public:
        BaseContext(Builder& builder);
        DictItemContext StartDict();
        ArrayItemContext StartArray();
        Builder& EndDict();
        Builder& EndArray();
        KeyItemContext Key(std::string key);
        Builder& Value(Node value);
    private:
        Builder& builder_;
    };

    class KeyItemContext : public BaseContext {
    public:
        KeyItemContext(Builder& builder);
        KeyItemContext Value(Node value);

        Builder& EndArray() = delete;
        DictItemContext StartDict() = delete;
    };

    class DictItemContext : public BaseContext{
    public:
        DictItemContext(Builder& builder);

        DictItemContext StartDict() = delete;
        ArrayItemContext StartArray() = delete;
        Builder& EndArray() = delete;
        Builder& Value(Node value) = delete;
        Node Build() = delete;
    };

    class ArrayItemContext : public BaseContext {
    public:
        ArrayItemContext(Builder& builder);
        ArrayItemContext Value(Node value);

        Builder& EndDict() = delete;
        KeyItemContext Key(std::string key) = delete;
    };

    class Builder {
    public:
        Builder();
        DictItemContext StartDict();
        ArrayItemContext StartArray();

        Builder& EndDict();
        Builder& EndArray();
        Builder& Value(const Node& value);

        KeyItemContext Key(std::string key);
        Node Build();
    private:
        Node root_;
        std::vector<Node*> nodes_stack_;
    };
}