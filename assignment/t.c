 "your.version.here"

metadata:
  name: "your-flow-name"
  description: "A brief description of your flow"
  author: "your-username"
  tags: [tag1, tag2, tag3]
  private: false

inputs:
  input1:
    type: string
    description: "Description of input1"
    required: true
    example: "Example value for input1"

model:
  provider: "provider-name"
  name: "model-name"

dataset:
  source: "author_name/dataset_name"

prompt: |
  Your flow's primary instruction or role...
  You can use {input1} placeholders to reference inputs.

readme: |
  Your flow's readme...
  You can use raw text or markdown here.
