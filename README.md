<h4 align="center">Condition-Zero Tutor notifications in CS 1.6</h4>

<p align="center">Send Condition-Zero Tutor notifications for Players in CS 1.6.</p>

<p align="center">
    <a href="https://github.com/SmileYzn/tutor/issues"><img alt="GitHub Issues" src="https://img.shields.io/github/issues-raw/smileyzn/tutor?style=flat-square"></a>
    <a href="https://github.com/SmileYzn/tutor/actions"><img alt="GitHub Workflow Status" src="https://img.shields.io/github/actions/workflow/status/SmileYzn/tutor/build.yml?branch=main&label=Build&style=flat-square"></a>
</p>

<p>Plugin commands</p>

| Command                             | Parameters                                      | Description                                     |
| :---------------------------------- | :---------------------------------------------- | :---------------------------------------------- |
| cs_tutor_show                       | <name or #userid> <0~8> <hold_time> <text_msg>        | Send the message in notifiction tutor           |
| cs_tutor_hide                       | <name or #userid>                               | Hide current player tutor message               |

<p>Colors parameter 0~8</p>

| Number | Color | Icon  |
| :---------------------------------- | :---------------------------------- | :----------------------------------|
| 0 | 🟦 | ℹ️ |
| 1 | 🟥 | ☠️ |
| 2 | 🟦 | ☠️ |
| 3 | 🟨 | ℹ️ |
| 4 | 🟩 | ℹ️ |
| 5 | 🟩 | ℹ️ |
| 6 | 🟩 | ℹ️ |
| 7 | 🟩 | ℹ️ |
| 8 | 🟨 | ℹ️ |

<h5>Know Issues</h5>
<ul>
    <li>At first player join, after he downloaded tutor resources, the notification will be buggy duo a engine limitation</li>
    <li>This is a illegal approach to send CZ Tutor notifications on CS 1.6, use at own risk</li>
</ul>